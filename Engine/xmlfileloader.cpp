#include "xmlfileloader.h"

#include <fstream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <set>
#include <cstdlib>

#include <boost/foreach.hpp>

#include "include/rapidxml_print.hpp"

#include "interfaces/isimulationcore.h"

using namespace rapidxml;

XMLFileLoader::XMLFileLoader()
{
    this->lastError = "";
}

std::string XMLFileLoader::getFileMatchPattern()
{
    return "\\.simx$";
}

std::string XMLFileLoader::getFileTypeName()
{
    return "XML Simulation Files (*.simx)";
}

boost::shared_ptr<ISimulation> XMLFileLoader::loadFile(ISimulationCore *core, std::string fileName)
{
    //load the entire file into a string
    std::ifstream file(fileName.c_str());
    if (!file.is_open())
    {
        this->lastError = "Unable to open file";
        return boost::shared_ptr<ISimulation>(); //null because there was an error
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    //load up the document parser
    xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    //find the simulation tag
    xml_node<>* simulationNode = doc.first_node("simulation");

    if (!simulationNode)
    {
        this->lastError = "Missing root <simulation>";
        return boost::shared_ptr<ISimulation>(); //null since there was no simulation
    }

    xml_attribute<>* rootModelNameAttribute = simulationNode->first_attribute("root");

    if (!rootModelNameAttribute)
    {
        this->lastError = "Missing root model entry point name";
        return boost::shared_ptr<ISimulation>(); //null since no entry point was specified
    }

    std::string rootModelName = rootModelNameAttribute->value();

    xml_attribute<>* stepsAttribute = simulationNode->first_attribute("steps");
    xml_attribute<>* deltaAttribute = simulationNode->first_attribute("delta");
    //assume 0 steps and 1 for the delta
    int steps = 0;
    double delta = 1;
    if (stepsAttribute) //we have some steps!
        steps = atoi(stepsAttribute->value());
    if (deltaAttribute) //we have a delta!
        delta = atof(deltaAttribute->value());


    //first pass through the models: create them with entries and exits
    std::map<std::string, std::pair<xml_node<>*, boost::shared_ptr<IModel> > > models;
    for(xml_node<>* modelNode = simulationNode->first_node("model"); modelNode; modelNode = modelNode->next_sibling("model"))
    {
        xml_attribute<>* nameAttribute = modelNode->first_attribute("name");
        if (!nameAttribute)
            continue; //skip this model since it has no name

        boost::shared_ptr<IModel> model = core->createModel(nameAttribute->value());

        /**
         * TODO: Move all of these into the same loop
         * so that this is a little more efficient (it is scanning the block list
         * 2 times this way)
         */

        //add entries
        for(xml_node<>* i = modelNode->first_node("entry"); i; i = i->next_sibling("entry"))
        {
            nameAttribute = i->first_attribute("name");
            if (!nameAttribute)
                continue; //skip this entry since it has no name

            xml_attribute<>* idAttribute = i->first_attribute("id");
            if (!idAttribute)
                continue; //skip this entry since it has no id
            int id = atoi(idAttribute->value());

            boost::shared_ptr<IEntryBlock> block = model->addEntry(id, nameAttribute->value());

            if (!block)
                continue; //to add data we need a block...

            //add the data to the block
            this->readBlockData(i, block);
        }

        //add exits
        for(xml_node<>* i = modelNode->first_node("exit"); i; i = i->next_sibling("exit"))
        {
            nameAttribute = i->first_attribute("name");
            if (!nameAttribute)
                continue; //skip this exit since it has no name

            xml_attribute<>* idAttribute = i->first_attribute("id");
            if (!idAttribute)
                continue; //skip this entry since it has no id
            int id = atoi(idAttribute->value());

            boost::shared_ptr<IExitBlock> block = model->addExit(id, nameAttribute->value());

            if (!block)
                continue; //to add data we need a block...

            //add the data to the block
            this->readBlockData(i, block);
        }

        //save it
        models[model->getName()] = std::pair<xml_node<>*, boost::shared_ptr<IModel> >(modelNode, model);
    }

    typedef std::pair<std::string, std::pair<xml_node<>*, boost::shared_ptr<IModel> > > ModelRecord;
    BOOST_FOREACH(ModelRecord modelRecord, models)
    {
        boost::shared_ptr<IModel> model = modelRecord.second.second;

        xml_node<>* modelNode = modelRecord.second.first;

        /**
         * TODO: Move all of these into the same loop (except connections)
         * so that this is a little more efficient (it is scanning the block list
         * 3 times this way)
         */

        //go through all the sub models
        for(xml_node<>* i = modelNode->first_node("model"); i; i = i->next_sibling("model"))
        {
            xml_attribute<>* nameAttribute = i->first_attribute("model");
            xml_attribute<>* idAttribute = i->first_attribute("id");
            if (!nameAttribute || !idAttribute)
            {
                std::cout << "no name for model block" << std::endl;
                continue; //no name or id? skip
            }

            int id = atoi(idAttribute->value());

            if (!models.count(nameAttribute->value()))
            {
                std::cout << "model " << nameAttribute->value() << " doesn't exist" << std::endl;
                continue; //the model doesn't exist
            }

            boost::shared_ptr<IModelBlock> block = model->addModel(id, models.at(nameAttribute->value()).second);

            //TODO: Do we want an exception when this returns null? That means there was infinite recursion

            if (!block)
            {
                std::cout << "Unable to create a modelblock " << std::endl;
                continue; //to add data we need a block...
            }

            //add the data to the block
            std::cout << "reading block data" << std::endl;
            this->readBlockData(i, block);
        }

        //go through all the normal blocks
        std::cout << "going through normal blocks..." << std::endl;
        for(xml_node<>* i = modelNode->first_node("block"); i; i = i->next_sibling("block"))
        {
            xml_attribute<>* idAttribute = i->first_attribute("id");
            xml_attribute<>* nameAttribute = i->first_attribute("name");
            xml_attribute<>* groupAttribute = i->first_attribute("group");

            if (!idAttribute || !nameAttribute || !groupAttribute)
                continue; //id, name, and group are required

            int id = atoi(idAttribute->value());

            boost::shared_ptr<IBlock> block = model->createBlock(id, groupAttribute->value(), nameAttribute->value());

            if (!block)
                continue; //to add data we need a block...

            //add the data to the block
            this->readBlockData(i, block);
        }

        //go through all the connections
        for(xml_node<>* i = modelNode->first_node("connection"); i; i = i->next_sibling("connection"))
        {
            xml_attribute<>* fromAttribute = i->first_attribute("from");
            xml_attribute<>* outputAttribute = i->first_attribute("output");
            xml_attribute<>* toAttribute = i->first_attribute("to");
            xml_attribute<>* inputAttribute = i->first_attribute("input");

            if (!fromAttribute || !outputAttribute || !toAttribute || !inputAttribute)
                continue; //these are all required

            int fromId = atoi(fromAttribute->value());
            int toId = atoi(toAttribute->value());

            boost::shared_ptr<IBlock> fromBlock = model->getBlock(fromId);
            boost::shared_ptr<IBlock> toBlock = model->getBlock(toId);

            if (!fromBlock || !toBlock)
                continue; //both blocks must exist

            //TODO: Should something happen when this fails?
            fromBlock->connect(outputAttribute->value(), toBlock, inputAttribute->value(), false);
        }
    }

    //create the simuation object
    boost::shared_ptr<ISimulation> simulation = core->createSimulation(steps, delta, fileName);

    //add all the models
    BOOST_FOREACH(ModelRecord modelRecord, models)
    {
        boost::shared_ptr<IModel> model = modelRecord.second.second;
        simulation->addModel(model);
    }
    //set the root model
    simulation->setRootModel(rootModelName);

    //close the file
    file.close();

    return simulation;
}

bool XMLFileLoader::saveFile(ISimulationCore *, boost::shared_ptr<ISimulation> simulation, std::string fileName)
{
    //does the simulation have a root model?
    if (!simulation->getRootModel())
        return false; //they need a root model first

    //attempt to open the file for writing
    std::ofstream file(fileName.c_str());
    if (!file.is_open())
        return false; //the file didn't open

    xml_document<> doc;

    xml_node<>* declaration = doc.allocate_node(node_declaration);
    declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    doc.append_node(declaration);

    xml_node<>* simulationNode = doc.allocate_node(node_element, "simulation");

    //set the steps, delta, and root model name
    std::stringstream s;
    s << simulation->getSteps();
    char* steps = doc.allocate_string(s.str().c_str());
    xml_attribute<>* tempAttribute = doc.allocate_attribute("steps", steps);
    simulationNode->append_attribute(tempAttribute);
    std::stringstream s1;
    s1 << simulation->getDelta();
    char* delta = doc.allocate_string(s1.str().c_str());
    tempAttribute = doc.allocate_attribute("delta", delta);
    simulationNode->append_attribute(tempAttribute);
    std::stringstream s2;
    s2 << simulation->getRootModel()->getName();
    char* rootModelName = doc.allocate_string(s2.str().c_str());
    tempAttribute = doc.allocate_attribute("root", rootModelName);
    simulationNode->append_attribute(tempAttribute);
    doc.append_node(simulationNode);

    std::map<std::string, boost::shared_ptr<IModel> > models = simulation->getModels();
    typedef std::pair<std::string, boost::shared_ptr<IModel> > ModelRecord;
    BOOST_FOREACH(ModelRecord modelRecord, models)
    {
        xml_node<>* modelNode = doc.allocate_node(node_element, "model");
        std::set<int> blocksAdded; //this helps separate the special blocks from normal blocks

        char* modelName = doc.allocate_string(modelRecord.second->getName().c_str());
        modelNode->append_attribute(doc.allocate_attribute("name", modelName));

        //go through entries
        typedef std::pair<std::string, boost::shared_ptr<IEntryBlock> > EntryRecord;
        BOOST_FOREACH(EntryRecord entryRecord, modelRecord.second->getEntries())
        {
            blocksAdded.insert(entryRecord.second->getId());

            boost::shared_ptr<IEntryBlock> block = entryRecord.second;

            //create the node for this block
            xml_node<>* blockNode = doc.allocate_node(node_element, "entry");
            char* name = doc.allocate_string(block->getEntryName().c_str());
            blockNode->append_attribute(doc.allocate_attribute("name", name));
            std::stringstream s;
            s << block->getId();
            char* id = doc.allocate_string(s.str().c_str());
            blockNode->append_attribute(doc.allocate_attribute("id", id));

            this->appendDataToBlockNode(&doc, blockNode, block);

            modelNode->append_node(blockNode);
            this->attachConnectionsToModel(&doc, modelNode, id, block);
        }

        //go through exits
        typedef std::pair<std::string, boost::shared_ptr<IExitBlock> > ExitRecord;
        BOOST_FOREACH(ExitRecord exitRecord, modelRecord.second->getExits())
        {
            blocksAdded.insert(exitRecord.second->getId());

            boost::shared_ptr<IExitBlock> block = exitRecord.second;

            //create the node for this block
            xml_node<>* blockNode = doc.allocate_node(node_element, "exit");
            char* name = doc.allocate_string(block->getExitName().c_str());
            blockNode->append_attribute(doc.allocate_attribute("name", name));
            std::stringstream s;
            s << block->getId();
            char* id = doc.allocate_string(s.str().c_str());
            blockNode->append_attribute(doc.allocate_attribute("id", id));

            this->appendDataToBlockNode(&doc, blockNode, block);

            modelNode->append_node(blockNode);
            this->attachConnectionsToModel(&doc, modelNode, id, block);
        }

        //go through modelblocks
        typedef std::pair<int, boost::shared_ptr<IModelBlock> > ModelBlockRecord;
        BOOST_FOREACH(ModelBlockRecord modelBlockRecord, modelRecord.second->getModelBlocks())
        {
            blocksAdded.insert(modelBlockRecord.second->getId());

            boost::shared_ptr<IModelBlock> block = modelBlockRecord.second;

            //create the node for this block
            xml_node<>* blockNode = doc.allocate_node(node_element, "model");
            char* name = doc.allocate_string(block->getModel()->getName().c_str()); //model name
            blockNode->append_attribute(doc.allocate_attribute("model", name));
            std::stringstream s;
            s << block->getId();
            char* id = doc.allocate_string(s.str().c_str());
            blockNode->append_attribute(doc.allocate_attribute("id", id));

            this->appendDataToBlockNode(&doc, blockNode, block);

            modelNode->append_node(blockNode);
            this->attachConnectionsToModel(&doc, modelNode, id, block);
        }

        //go through the rest
        typedef std::pair<int, boost::shared_ptr<IBlock> > BlockRecord;
        BOOST_FOREACH(BlockRecord blockRecord, modelRecord.second->getBlocks())
        {
            if (blocksAdded.count(blockRecord.second->getId()))
                continue; //skip this block since its already been added

            boost::shared_ptr<IBlock> block = blockRecord.second;

            //create the node for this block
            xml_node<>* blockNode = doc.allocate_node(node_element, "block");
            char* name = doc.allocate_string(block->getName().c_str());
            blockNode->append_attribute(doc.allocate_attribute("name", name));
            char* group = doc.allocate_string(block->getGroup().c_str());
            blockNode->append_attribute(doc.allocate_attribute("group", group));
            std::stringstream s;
            s << block->getId();
            char* id = doc.allocate_string(s.str().c_str());
            blockNode->append_attribute(doc.allocate_attribute("id", id));

            this->appendDataToBlockNode(&doc, blockNode, block);

            modelNode->append_node(blockNode);
            this->attachConnectionsToModel(&doc, modelNode, id, block);
        }

        simulationNode->append_node(modelNode);
    }

    //write the document out to the file
    file << doc;
    file.close();

    //the simulation now has a filename
    simulation->setFileName(fileName);
    return true;
}

const std::string &XMLFileLoader::getLastError() const
{
    return this->lastError;
}

void XMLFileLoader::appendDataToBlockNode(xml_document<>* doc, rapidxml::xml_node<> *blockNode, boost::shared_ptr<IBlock> block)
{
    //append options
    for(std::map<std::string, boost::shared_ptr<std::vector<double> > >::const_iterator iter = block->getOptions().begin(); iter != block->getOptions().end(); iter++)
    {
        char* optionName = doc->allocate_string((*iter).first.c_str());
        xml_node<>* option = doc->allocate_node(node_element, "option");
        option->append_attribute(doc->allocate_attribute("name", optionName));
        for(std::vector<double>::const_iterator iter2 = (*iter).second->begin(); iter2 != (*iter).second->end(); iter2++)
        {
            std::stringstream s;
            s << (*iter2);
            char* value = doc->allocate_string(s.str().c_str());
            option->append_node(doc->allocate_node(node_element, "value", value));
        }

        blockNode->append_node(option);
    }
    //append actual data
    for(std::map<std::string, std::string>::const_iterator iter = block->getData().begin(); iter != block->getData().end(); iter++)
    {
        char* name = doc->allocate_string((*iter).first.c_str());
        char* value = doc->allocate_string((*iter).second.c_str());
        xml_node<>* dataNode = doc->allocate_node(node_element, "data", value);
        dataNode->append_attribute(doc->allocate_attribute("name", name));

        blockNode->append_node(dataNode);
    }
}

void XMLFileLoader::attachConnectionsToModel(xml_document<> *doc, rapidxml::xml_node<> *modelNode, char* id, boost::shared_ptr<IBlock> block)
{
    //go through the connections for this block
    typedef std::pair<std::string, boost::shared_ptr<IBlockOutput> > OutputRecord;
    BOOST_FOREACH(OutputRecord outputRecord, block->getOutputs())
    {
        BOOST_FOREACH(boost::shared_ptr<IBlockInput> input, outputRecord.second->getAttachedInputs())
        {
            xml_node<>* connection = doc->allocate_node(node_element, "connection");
            connection->append_attribute(doc->allocate_attribute("from", id));
            char* output = doc->allocate_string(outputRecord.first.c_str());
            connection->append_attribute(doc->allocate_attribute("output", output));
            std::stringstream s;
            s << input->getBlockId();
            char* to = doc->allocate_string(s.str().c_str());
            connection->append_attribute(doc->allocate_attribute("to", to));
            char* inputName = doc->allocate_string(input->getName().c_str());
            connection->append_attribute(doc->allocate_attribute("input", inputName));

            modelNode->append_node(connection);
        }
    }
}

void XMLFileLoader::readBlockData(rapidxml::xml_node<> *blockNode, boost::shared_ptr<IBlock> block)
{
    //read options
    for(xml_node<>* i = blockNode->first_node("option"); i; i = i->next_sibling("option"))
    {
        xml_attribute<>* name = i->first_attribute("name");
        if (name)
        {
            boost::shared_ptr<std::vector<double> > value(new std::vector<double>());
            //find out its value
            for(xml_node<>* j = i->first_node("value"); j; j = j->next_sibling("value"))
            {
                value->push_back(atof(j->value()));
            }

            if (value->size())
            {
                block->setOption(name->value(), value);
            }
        }
    }
    //read data
    for(xml_node<>* i = blockNode->first_node("data"); i; i = i->next_sibling("data"))
    {
        xml_attribute<>* name = i->first_attribute("name");
        if (name)
        {
            block->setData(name->value(), i->value());
        }
    }
}
