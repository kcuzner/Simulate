#include "context.h"
#include "input.h"
#include "block.h"
#include "model.h"

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

void Context::queueBlock(QSharedPointer<Block> block)
{
    this->execute.enqueue(block);
}

void Context::step()
{

    this->initialize(); //initialize all our blocks

    int executions = 0;
    while(!this->execute.empty())
    {
        //dequeue a block in the execution queue
        QSharedPointer<Block> blk = this->execute.dequeue();

        blk->execute(this);

        executions++;
    }

    emit(this->finished(executions));
}

void Context::initialize()
{
    QList<QSharedPointer<Block> > blocks = this->model->getBlocks();
    for(QList<QSharedPointer<Block> >::iterator i = blocks.begin(); i != blocks.end(); i++)
    {
        QSharedPointer<Block> blk = (*i);
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

QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > Context::getPersistantBlockContext(Block *instance)
{
    if (this->variableContexts.contains(instance))
    {
        return this->variableContexts[instance];
    }

    //create a new context for this instance
    QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context(new QHash<QString,QSharedPointer<QList<double> > >());
    this->variableContexts[instance] = context;

    return context;
}

QSharedPointer<QList<double> > Context::getInputValue(Input *input)
{
    if (this->inputValues.contains(input))
        return this->inputValues[input];
    else
        return QSharedPointer<QList<double> >(); //return null
}

QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > Context::getBlockInputs(Block *instance)
{
    QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputValues(new QHash<QString, QSharedPointer<QList<double> > >());

    QHash<QString, QSharedPointer<Input> > inputs = instance->getInputs();
    QSharedPointer<Input> input;
    foreach(input, inputs.values())
    {
        (*inputValues)[input->getName()] = this->getInputValue(input.data());
    }

    return inputValues;
}

void Context::reset()
{
    this->variableContexts.clear(); //because this is a hashset of QSharedPointers, this shouldn't cause a memory leak
}

void Context::setInput(Input *input, QSharedPointer<QList<double> > value)
{
    this->inputValues[input] = value;
}
