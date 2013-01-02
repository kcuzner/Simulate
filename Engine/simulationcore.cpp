#include "simulationcore.h"

#include "defaultblockfactory.h"
#include "simpleengine.h"
#include "model.h"

#include <boost/foreach.hpp>

SimulationCore::SimulationCore()
{
    this->blockFactory = DefaultBlockFactory::getInstance();

    this->addEngineType("simple", SimpleEngine::generate);
    this->setEngineType("simple");

    boost::shared_ptr<IModelGenerator> modelGenerator(new ModelGenerator());
    this->addModelType(modelGenerator);
    this->setModelType(modelGenerator->getModelTypeName());
}

boost::shared_ptr<SimulationCore> SimulationCore::instance;
boost::shared_ptr<ISimulationCore> SimulationCore::getInstance()
{
    if (!instance)
        instance = boost::shared_ptr<SimulationCore>(new SimulationCore());

    return instance;
}

bool SimulationCore::addEngineType(const std::string &name, boost::function<boost::shared_ptr<IEngine> (boost::shared_ptr<IModel>, int, double)> generator)
{
    if (this->engineGenerators.count(name))
        return false;

    if (!this->engineGenerators.size())
        this->engineType = name;

    this->engineGenerators[name] = generator;

    return true;
}

boost::shared_ptr<IEngine> SimulationCore::createEngine(const std::string &name, boost::shared_ptr<IModel> model, int steps, double delta)
{
    return this->engineGenerators[name](model, steps, delta);
}

boost::shared_ptr<IEngine> SimulationCore::createEngine(boost::shared_ptr<IModel> model, int steps, double delta)
{
    return this->createEngine(this->engineType, model, steps, delta);
}

void SimulationCore::setEngineType(const std::string &typeName)
{
    if (!this->engineGenerators.count(typeName))
        return;

    this->engineType = typeName;
}

bool SimulationCore::addModelType(boost::shared_ptr<IModelGenerator> generator)
{
    if (this->modelTypes.count(generator->getModelTypeName()))
        return false;

    this->modelTypes[generator->getModelTypeName()] = generator;

    return true;
}

boost::shared_ptr<IModel> SimulationCore::createModel(const std::string &modelTypeName, const std::string &modelName)
{
    return this->modelTypes[modelTypeName]->generate(modelName, blockFactory);
}

boost::shared_ptr<IModel> SimulationCore::createModel(const std::string &name)
{
    return this->createModel(this->modelType, name);
}

void SimulationCore::setModelType(const std::string &modelTypeName)
{
    this->modelType = modelTypeName;
}

bool SimulationCore::addBlockCollection(boost::shared_ptr<IBlockCollection> collection)
{
    collection->declareToFactory(this->blockFactory);
    return true;
}

bool SimulationCore::addFileLoader(boost::shared_ptr<IFileLoader> loader)
{
    if (this->fileLoaders.count(loader->getFileMatchPattern()))
        return false; //something has already claimed that pattern

    this->fileLoaders[loader->getFileMatchPattern()] = loader;

    return true;
}

boost::shared_ptr<ISimulation> SimulationCore::loadSimulation(const std::string &fileName)
{
    //go through the list of file loaders and the first one to match gets to load it
    typedef std::pair<std::string, boost::shared_ptr<IFileLoader> > LoaderRecord;
    boost::shared_ptr<IFileLoader> loader;
    BOOST_FOREACH(LoaderRecord loaderRecord, this->fileLoaders)
    {
        /*boost::regex r(loaderRecord.first);
        if (boost::regex_match(fileName, r))
        {
            loader = loaderRecord.second;
            break;
        }*/
    }

    if (loader)
    {
        //we found one!
        return loader->loadFile(this, fileName);
    }

    //if we made it this far, we couldn't load the file
    return boost::shared_ptr<ISimulation>();
}

bool SimulationCore::saveSimulation(boost::shared_ptr<ISimulation> simulation, const std::string &fileName)
{
    //go through the list of file loaders and the first one to match gets to save it
    typedef std::pair<std::string, boost::shared_ptr<IFileLoader> > LoaderRecord;
    boost::shared_ptr<IFileLoader> loader;
    BOOST_FOREACH(LoaderRecord loaderRecord, this->fileLoaders)
    {
        /*boost::regex r(loaderRecord.first);
        if (boost::regex_match(fileName, r))
        {
            loader = loaderRecord.second;
            break;
        }*/
    }

    if (loader)
    {
        //we found one!
        return loader->saveFile(this, simulation, fileName);
    }

    //if we made it this far, we couldn't load the file
    return false;
}

const std::string &SimulationCore::getLastFileError()
{
}

boost::shared_ptr<ISimulation> SimulationCore::createSimulation(int steps, double delta)
{
}