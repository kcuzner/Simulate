#include "input.h"
#include "block.h"
#include "output.h"

using namespace Simulation;

Input::Input(Block *parent, QString name) :
    QObject(parent)
{
    this->block = parent;
    this->name = name;
}

Input::~Input()
{
    //disconnect this input from all the outputs
    for(QSet<Output*>::iterator i = this->connected.begin(); i != this->connected.end(); i++)
    {
        (*i)->disconnect(this, false);
    }
}

QString Input::getName()
{
    return this->name;
}

void Input::connect(Output *output, bool backRef)
{
    if (this->connected.contains(output))
        return; //don't double connect outputs

    if (backRef)
    {
        //by default, we create double link but prevent the output from creating an infinite loop and linking
        //back to us.
        output->connect(this, false);
    }

    this->connected.insert(output);
}

void Input::disconnect(Output *output, bool backRef)
{
    if (!this->connected.contains(output))
        return; //no need to remove something that isn't there

    if (backRef)
    {
        //disconnect this from the output
        output->disconnect(this, false);
    }

    this->connected.remove(output);
}

void Input::set(Context *context, SignalValue value)
{
}
