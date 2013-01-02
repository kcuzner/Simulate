#define BOOST_TEST_MODULE MainTest
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include <iostream>

#include "defaultblockfactory.h"
#include "system/systemblocks.h"
#include "model.h"
#include "simulationcore.h"

BOOST_AUTO_TEST_CASE( declareBlocks )
{
    //if this completes without throwing exceptions, we assume it can declare blocks

    boost::shared_ptr<IBlockFactory> factory = DefaultBlockFactory::getInstance();

    boost::shared_ptr<IBlockCollection> systemBlocks(new System::SystemBlocks());

    systemBlocks->declareToFactory(factory);
}

BOOST_AUTO_TEST_CASE( instantiateBlocks )
{
    boost::shared_ptr<IBlockFactory> factory = DefaultBlockFactory::getInstance();

    boost::shared_ptr<IBlockCollection> systemBlocks(new System::SystemBlocks());

    systemBlocks->declareToFactory(factory);

    //instantiate a block that exists
    boost::shared_ptr<IBlock> block = factory->generateBlock(6, "Var", "Static");

    if (!block)
    {
        BOOST_FAIL("Returned null trying to instantiate Var.Static");
    }
    else
    {
        BOOST_CHECK_EQUAL(block->getId(), 6);
        BOOST_CHECK_EQUAL(block->getGroup(), "Var");
        BOOST_CHECK_EQUAL(block->getName(), "Static");
    }

    //try to instantiate a block that doesn't exist
    block = factory->generateBlock(6, "var", "static");
    if (block)
    {
        BOOST_FAIL("Returned non-null trying to instantiate var.static (which shouldn't exist...capitalization)");
    }
}

BOOST_AUTO_TEST_CASE( runSimulation )
{
    boost::shared_ptr<ISimulationCore> core = SimulationCore::getInstance();

    boost::shared_ptr<IModel> model = core->createModel("test");
    boost::shared_ptr<IEngine> engine = core->createEngine(model, 20, 0.1);

    //test a normal simulation multiplying two unchanging numbers together
    boost::shared_ptr<IBlock> block = model->createBlock("Var", "Static");
    boost::shared_ptr<std::vector<double> > value(new std::vector<double>());
    value->push_back(5.5);
    block->setOption(engine->getContext().get(), "Value", value);

    boost::shared_ptr<IBlock> block2 = model->createBlock("Var", "Static");
    value = boost::shared_ptr<std::vector<double> >(new std::vector<double>());
    value->push_back(2.0);
    block2->setOption(engine->getContext().get(), "Value", value);

    boost::shared_ptr<IBlock> block3 = model->createBlock("Math", "Multiply");

    BOOST_CHECK(block->connect("Output", block3, "Multiplicand 1", false));
    BOOST_CHECK(block2->connect("Output", block3, "Multiplicand 2", false));

    block = model->addExit("Result");
    BOOST_CHECK(block3->connect("Product", block, IEXITBLOCK_INPUT_NAME, false));

    engine->run();

    BOOST_CHECK_EQUAL(model->getExits().at("Result")->getCurrentValue(engine->getContext().get())->at(0), 11.0);

    //create a sub-model executing inside a model twice
    std::cout << std::endl << std::endl;
    boost::shared_ptr<IModel> integration = core->createModel("integration");

    integration->addEntry("Accumulation");
    integration->addExit("Accumulation");
    integration->addEntry("Input");
    integration->addExit("Value");

    block = integration->createBlock("Math", "Multiply");

    BOOST_CHECK(integration->getEntries().at("Accumulation")->connect(IENTRYBLOCK_OUTPUT_NAME, block, "Multiplicand 1", false));
    BOOST_CHECK(integration->getEntries().at("Input")->connect(IENTRYBLOCK_OUTPUT_NAME, block, "Multiplicand 2", false));

    BOOST_CHECK(block->connect("Product", integration->getExits().at("Accumulation"), IEXITBLOCK_INPUT_NAME, false));
    BOOST_CHECK(block->connect("Product", integration->getExits().at("Value"), IEXITBLOCK_INPUT_NAME, false));

    model = core->createModel("test");
    engine = core->createEngine(model, 5, 0.1);
    block = model->addModel(integration);
    std::cout << "model 1 id " << block->getId() << std::endl;
    if (!block)
        BOOST_FAIL("Returned null creating block from model 1st time.");

    typedef std::pair<std::string, boost::shared_ptr<IBlockOutput> > OutputRecord;
    BOOST_FOREACH(OutputRecord record, block->getOutputs())
    {
        std::cout << record.first << std::endl;
    }

    block2 = model->addModel(integration);
    std::cout << "model 2 id " << block2->getId() << std::endl;
    if (!block2)
        BOOST_FAIL("Returned null creating block from model 2nd time.");

    block->connect("Value", block2, "Input", true);
    block3 = model->createBlock("Var", "Static");
    std::cout << "static block id " << block3->getId() << std::endl;
    value = boost::shared_ptr<std::vector<double> >(new std::vector<double>());
    value->push_back(1.001);
    block3->setOption(engine->getContext().get(), "Value", value);
    BOOST_CHECK(block3->connect("Output", block, "Input", false));

    block = model->addExit("Result");
    if (!block)
        BOOST_FAIL("Unable to create exit Result");
    BOOST_CHECK(block2->connect("Value", block, IEXITBLOCK_INPUT_NAME, false));
    std::cout << "hi" << std::endl;

    engine->run();

    std::cout << model->getExits().at("Result")->getCurrentValue(engine->getContext().get()) << std::endl;
    std::cout << model->getExits().at("Result")->getCurrentValue(engine->getContext().get())->at(0) << std::endl;
}


BOOST_AUTO_TEST_CASE( instantiateModelBlock )
{
    boost::shared_ptr<IModel> model = SimulationCore::getInstance()->createModel("inside");

    model->addEntry("Entry 1");
    model->addEntry("Entry 2");

    model->addExit("Exit 1");
    model->addExit("Exit 2");
    model->addExit("Exit 3");

    boost::shared_ptr<IModel> root = SimulationCore::getInstance()->createModel("root");

    //test creating a block
    boost::shared_ptr<IModelBlock> modelBlock = root->addModel(model);

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs = modelBlock->getInputs();

    BOOST_CHECK(inputs.count("Entry 1"));
    BOOST_CHECK(inputs.count("Entry 2"));

    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs = modelBlock->getOutputs();

    BOOST_CHECK(outputs.count("Exit 1"));
    BOOST_CHECK(outputs.count("Exit 2"));
    BOOST_CHECK(outputs.count("Exit 3"));

    //test adding new inputs
    model->addEntry("Added entry");

    inputs = modelBlock->getInputs();

    BOOST_CHECK(inputs.count("Added entry"));

    //test removing an existing input
    model->removeEntry("Entry 2");

    inputs = modelBlock->getInputs();

    BOOST_CHECK(!inputs.count("Entry 2"));

    //test added new outputs
    model->addExit("Added exit");

    outputs = modelBlock->getOutputs();

    BOOST_CHECK(outputs.count("Added exit"));

    //test removing an existing output
    model->removeExit("Exit 2");

    outputs = modelBlock->getOutputs();

    BOOST_CHECK(!outputs.count("Exit 2"));

}
