#include "context.h"
#include "input.h"
#include "block.h"

#include <stdexcept>

using namespace std;
using namespace Simulation;

Context::Context(double timeStep, QObject *parent) :
    QObject(parent)
{
    this->setTimeStep(timeStep);
}

Context::Context(Context *parent) :
    QObject(parent)
{
    this->setTimeStep(parent->getTimeStep());
}

double Context::getTimeStep()
{
    return this->timeStep;
}

void Context::setTimeStep(double timeStep)
{
    if (timeStep < 0)
    {
        throw new std::out_of_range("timeStep");
    }
    this->timeStep = timeStep;

    for(QList<Context*>::Iterator i = this->children.begin(); i != this->children.end(); i++)
    {
        //update all our children to share our new timestep
        (*i)->setTimeStep(timeStep);
    }

}

Context *Context::createChildContext()
{
    Context* child = new Context(this);
    this->children.append(child);
    return child;
}

void Context::reset()
{
}

void Context::setInput(Input *input, SignalValue value)
{
}

Context::BlockData::BlockData(Block *block)
{
}

void Context::BlockData::reset()
{
}

void Context::BlockData::newStep()
{
}

void Context::BlockData::setValue(QString valueName, SignalValue value)
{
}

SignalValue Context::BlockData::getValue(QString valueName)
{
}
