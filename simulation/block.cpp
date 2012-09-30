#include "block.h"
#include "input.h"
#include "output.h"
#include "blockfactory.h"

using namespace Simulation;

Block::Block(QString name, QObject *parent) :
    QObject(parent)
{
    //declare this object in the block factory

}

QHash<QString, Input *> Block::getInputs()
{
    return this->inputs;
}

QHash<QString, Output *> Block::getOutputs()
{
    return this->outputs;
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

    emit(inputAdded(input));

    return input;
}

Output *Block::addOutput(QString name)
{
    if (this->outputs.contains(name))
    {
        //no need to add a new output if they already have one by this name
        return this->outputs[name];
    }

    Output* output = new Output(this, name);

    this->outputs[name] = output;

    emit(outputAdded(output));

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

    emit(inputRemoved(input));
}

void Block::removeInput(Input *input)
{
    if (!this->inputs.contains(input->getName()))
    {
        return;
    }

    this->removeInput(input->getName());
}

void Block::removeOutput(QString name)
{
    if (!this->inputs.contains(name))
    {
        return;
    }

    Output* output = this->outputs[name];

    this->outputs.remove(name);

    emit(outputRemoved(output));
}

void Block::removeOutput(Output *output)
{
    if (!this->outputs.contains(output->getName()))
    {
        return;
    }

    this->removeOutput(output->getName());
}
