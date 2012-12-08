#include "simpleengine.h"

#include "defaultblockfactory.h"
#include "defaultcontext.h"

#include <string>
#include <vector>

SimpleEngine::SimpleEngine()
{
    //create a default block factory
    this->currentFactory = boost::shared_ptr<IBlockFactory>(new DefaultBlockFactory());
}

boost::shared_ptr<IBlockFactory> SimpleEngine::getBlockFactory()
{
    return this->currentFactory;
}

void SimpleEngine::setBlockFactory(boost::shared_ptr<IBlockFactory> factory)
{
    this->currentFactory = factory;
}

boost::shared_ptr<IContext> SimpleEngine::createContext()
{
    return this->contextGenerator();
}

void SimpleEngine::setContextCreator(boost::function<boost::shared_ptr<IContext> ()> generator)
{
    this->contextGenerator = generator;
}

boost::shared_ptr<IContext> SimpleEngine::generateDefaultContext()
{
    return boost::shared_ptr<IContext>(new DefaultContext());
}
