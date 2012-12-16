#include "simpleengine.h"

#include "defaultblockfactory.h"
#include "defaultcontext.h"

#include <string>
#include <vector>

SimpleEngine::SimpleEngine(int steps, double delta)
{
    this->steps = steps;
    this->delta = delta;

    //create the block factory
    this->factory = DefaultBlockFactory::getInstance();
}

int SimpleEngine::getStepsToRun()
{
}

void SimpleEngine::setStepsToRun(int n)
{
}

double SimpleEngine::getStepDelta()
{
}

void SimpleEngine::setStepDelta(double d)
{
}

void SimpleEngine::run(boost::shared_ptr<IModel> model)
{
}

boost::shared_ptr<IBlockFactory> SimpleEngine::getBlockFactory()
{
}

boost::shared_ptr<IContext> SimpleEngine::setup(boost::shared_ptr<IModel> model)
{

}
