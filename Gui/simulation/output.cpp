#include "output.h"
#include "input.h"
#include "block.h"
#include "stepcontext.h"

using namespace Simulation;

Output::Output(Block *parent, QString name) :
    QObject(parent)
{
    this->block = block;
    this->name = name;
}

Output::~Output()
{
    //disconnect this output from all the inputs here
    for(QSet<Input*>::iterator i = this->connected.begin(); i != this->connected.end(); i++)
    {
        (*i)->disconnect(false);
    }
}

QString Output::getName()
{
    return this->name;
}

void Output::connect(Input *input, bool backRef)
{
    if (this->connected.contains(input))
        return; //skip this if we are already connected

    if (backRef)
    {
        //apply a back reference to the input
        input->connect(this, false);
    }

    this->connected.insert(input);
}

void Output::disconnect(Input *input, bool backRef)
{
    if (!this->connected.contains(input))
        return; //skip if this input isn't connected to this output

    if (backRef)
    {
        //apply a back reference to the input
        input->disconnect(false);
    }

    this->connected.remove(input);
}

void Output::set(StepContext *context, SignalValue* value)
{
    //when this output is set, we set all of our connected inputs to the passed value
    for(QSet<Input*>::iterator i = this->connected.begin(); i != this->connected.end(); i++)
    {
        //the step context holds the actual input values. Inputs are
        //merely fronts for getting the input from a context and serve
        //the main purpose of linking a block to an input.
        context->setInput((*i), value);
    }
}
