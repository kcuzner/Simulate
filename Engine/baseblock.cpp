#include "baseblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

BaseBlock::BaseBlock(int id, const std::string& group, const std::string& name)
{
    this->id = id;
    this->group = group;
    this->name = name;
}

int BaseBlock::getId()
{
    return id;
}

std::string BaseBlock::getGroup()
{
    return group;
}

std::string BaseBlock::getName()
{
    return name;
}

const std::map<std::string, boost::shared_ptr<IBlockInput> >& BaseBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> >& BaseBlock::getOutputs()
{
    return this->outputs;
}

boost::shared_ptr<IBlockInput> BaseBlock::addInput(const std::string &name)
{
    if (this->inputs.count(name))
        return boost::shared_ptr<IBlockInput>();

    boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this, name));

    this->inputs[name] = input;

    this->sigInputAdded(boost::weak_ptr<IBlockInput>(input));

    return input;
}

void BaseBlock::removeInput(const std::string &name)
{
    if (!this->inputs.count(name))
        return;

    boost::shared_ptr<IBlockInput> input = this->inputs[name];

    this->inputs.erase(name);

    this->sigInputRemoved(input);

    return;
}

boost::shared_ptr<IBlockOutput> BaseBlock::addOutput(const std::string &name)
{
    if (this->outputs.count(name))
        return boost::shared_ptr<IBlockOutput>();

    boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this, name));

    this->outputs[name] = output;

    this->sigOutputAdded(boost::weak_ptr<IBlockOutput>(output));

    return output;
}

void BaseBlock::removeOutput(const std::string &name)
{
    if (!this->outputs.count(name))
        return;

    boost::shared_ptr<IBlockOutput> output = this->outputs[name];

    this->outputs.erase(name);

    this->sigOutputRemoved(output);

    return;
}
