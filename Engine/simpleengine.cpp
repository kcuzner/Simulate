#include "simpleengine.h"

#include "defaultblockfactory.h"
#include "defaultcontext.h"

#include <string>
#include <vector>

SimpleEngine::SimpleEngine(boost::shared_ptr<IModel> model, int steps, double delta)
{
    this->model = model;

    this->steps = steps;
    this->delta = delta;

    //create our context
    this->context = boost::shared_ptr<IContext>(new DefaultContext(delta, model));

    //create the block factory
    this->factory = DefaultBlockFactory::getInstance();
}

unsigned int SimpleEngine::getStepsToRun()
{
    return steps;
}

void SimpleEngine::setStepsToRun(unsigned int n)
{
    steps = n;
}

double SimpleEngine::getStepDelta()
{
    return delta;
}

void SimpleEngine::setStepDelta(double d)
{
    delta = d;
}

boost::shared_ptr<IContext> SimpleEngine::getContext()
{
    return this->context;
}

boost::shared_ptr<IModel> SimpleEngine::getRootModel()
{
    return this->model;
}

void SimpleEngine::run()
{
    //reset the context
    this->context->reset();

    for(unsigned int i = 0; i < this->steps; i++)
    {
        //step the context
        this->context->step();

        //the step is finished, move on to the next one
        this->sigStepCompleted(this->model, i + 1, this->steps);
    }
}

boost::shared_ptr<IBlockFactory> SimpleEngine::getBlockFactory()
{
    return this->factory;
}
