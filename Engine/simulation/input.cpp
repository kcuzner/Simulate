#include "input.h"
#include "block.h"
#include "output.h"
#include "signalvalue.h"
#include "stepcontext.h"

using namespace Simulation;

Input::Input(Block *parent, QString name) :
    QObject(parent)
{
    this->block = parent;
    this->name = name;
    this->output = NULL;
}

Input::~Input()
{
    //disconnect this input from its output
    if (this->output != NULL)
    {
        this->output->disconnect(this, false);
    }
}

QString Input::getName()
{
    return this->name;
}

SignalValue *Input::getValue(StepContext *context)
{
    return NULL;
    //return context->getInputValue(this); //get our input value in this context
}

Block *Input::getBlock()
{
    return this->block;
}

bool Input::isConnected()
{
    return this->output != NULL;
}

void Input::connect(Output *output, bool backRef)
{
    if (this->output == output)
        return; //no need to do this again

    //if we are already connected, we get to disconnect
    this->disconnect();

    if (backRef)
    {
        //by default, we create double link but prevent the output from creating an infinite loop and linking
        //back to us.
        output->connect(this, false);
    }

    this->output = output;

    this->connected(output);
}

void Input::disconnect(bool backRef)
{
    if (this->output == NULL)
        return; //nothing to disconnect

    if (backRef)
    {
        //disconnect this from the output
        output->disconnect(this, false);
    }

    this->output = NULL; //we forget about the output

    this->disconnected();
}
