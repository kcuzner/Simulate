#include "input.h"
#include "block.h"
#include "output.h"

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

void Input::set(Context* context, SignalValue* value)
{

}
