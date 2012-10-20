#include "context.h"
#include "input.h"
#include "block.h"
#include "model.h"
#include "stepcontext.h"

#include <stdexcept>

using namespace std;
using namespace Simulation;

Context::Context(Model* model, double timeStep, QObject *parent) :
    QObject(parent)
{
    this->setTimeStep(timeStep);
    this->model = model;
}

Context::Context(Model* model, Context *parent) :
    QObject(parent)
{
    this->setTimeStep(parent->getTimeStep());
    this->model = model;
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

void Context::queueBlock(Block *block)
{
    this->execute.enqueue(block);
}

void Context::step()
{
    StepContext* context = new StepContext(this); //create a new step context

    this->initialize(); //initialize all our blocks

    int executions = 0;
    while(!this->execute.empty())
    {
        //dequeue a block in the execution queue
        Block* blk = this->execute.dequeue();

        blk->execute(context);

        executions++;
    }

    emit(this->finished(executions));

    delete context;
}

void Context::initialize()
{
    QList<Block*> blocks = this->model->getBlocks();
    for(QList<Block*>::iterator i = blocks.begin(); i != blocks.end(); i++)
    {
        Block* blk = (*i);
        blk->initialize(this);

        if (blk->getInputs().count() == 0)
        {
            //queue up blocks that don't have any inputs for execution
            this->queueBlock(blk);
        }
    }
}

Context *Context::createChildContext(Model* model)
{
    Context* child = new Context(model, this);
    this->children.append(child);
    return child;
}

void Context::reset()
{
}

void Context::setInput(Input *input, SignalValue* value)
{
}
