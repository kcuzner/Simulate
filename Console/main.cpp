#include <QCoreApplication>

#include "model.h"
#include "defaultblockfactory.h"
#include "simpleengine.h"

#include "system/systemblocks.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Creating system blocks container" << std::endl;
    boost::shared_ptr<System::SystemBlocks> systemBlocks(new System::SystemBlocks());

    std::cout << "Declaring blocks" << std::endl;
    systemBlocks->declareToFactory(DefaultBlockFactory::getInstance());

    boost::shared_ptr<Model> model(new Model(DefaultBlockFactory::getInstance()));

    boost::shared_ptr<IBlock> block = model->createBlock("Var", "Static");

    boost::shared_ptr<IEngine> engine(new SimpleEngine(model, 20, 0.001));
    boost::shared_ptr<std::vector<double> > value(new std::vector<double>());
    value->push_back(1.587);

    block->setOption(engine->getContext().get(), "Value", value);

    std::cout << block->getOption(engine->getContext().get(), "Value");

    boost::shared_ptr<IExitBlock> exit = model->addExit("Output");

    block->connect("Output", exit, IEXITBLOCK_INPUT_NAME, true);

    engine->run();

    std::cout << exit->getCurrentValue(engine->getContext().get()) << std::endl;

    std::cout << "All done" << std::endl;
    
    return a.exec();
}
