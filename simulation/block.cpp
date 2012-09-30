#include "block.h"
#include "input.h"
#include "output.h"

using namespace Simulation;

Block::Block(QObject *parent) :
    QObject(parent)
{
}

Input *Block::addInput(QString name)
{
    if (this->inputs.contains(name))
    {
        //no need to add a new one if they already have one by this name
        return this->inputs[name];
    }

    Input* input = new Input(this, name);

    this->inputs[name] = input;

    this->inputAdded(input);

    return input;
}

Output *Block::addOutput(QString name)
{
    if (this->outputs.contains(name))
    {
        //no need to add a new output if they already have one by this name
        return this->inputs[name];
    }

    Output* output = new Output(this, name);

    this->outputs[name] = output;

    this->outputAdded(output);

    return output;
}

void Block::removeInput(QString name)
{
    if (!this->inputs.contains(name))
    {
        return; //no need for removing something that doesn't exist
    }

    Input* input = this->inputs[name];

    this->inputs.remove(name);

    this->inputRemoved(input);
}

void Block::removeInput(Input *input)
{
}

void Block::removeOutput(QString name)
{
}

void Block::removeOutput(Input *input)
{
}
