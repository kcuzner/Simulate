#include "engine.h"

#include "defaultblockfactory.h"
#include "defaultcontext.h"

#include <string>
#include <vector>

Engine::Engine()
{
    //create a default block factory
    this->currentFactory = boost::shared_ptr<IBlockFactory>(new DefaultBlockFactory());
}

boost::shared_ptr<IBlockFactory> Engine::getBlockFactory()
{
    return this->currentFactory;
}

void Engine::setBlockFactory(boost::shared_ptr<IBlockFactory> factory)
{
    this->currentFactory = factory;
}

boost::shared_ptr<IContext> Engine::createContext()
{
    return this->contextGenerator();
}

void Engine::setContextCreator(boost::function<boost::shared_ptr<IContext> ()> generator)
{
    this->contextGenerator = generator;
}

boost::shared_ptr<IContext> Engine::generateDefaultContext()
{
    return boost::shared_ptr<IContext>(new DefaultContext());
}
