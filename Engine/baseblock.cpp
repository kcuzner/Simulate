#include "baseblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

#include <algorithm>

BaseBlock::BaseBlock(long id, const std::string& group, const std::string& name)
{
    this->id = id;
    this->group = group;
    this->name = name;
}

long BaseBlock::getId()
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

const std::list<std::string> &BaseBlock::getOptionNames()
{
    return this->options;
}

boost::shared_ptr<std::vector<double> > BaseBlock::getOption(IContext *context, const std::string &name)
{
    std::list<std::string>::iterator iter = std::find(this->options.begin(), this->options.end(), name);

    if (iter != this->options.end())
    {
        //we found it!
        return context->getStoredValue(this->getId(), name);
    }

    //if we made it this far it wasn't found
    return boost::shared_ptr<std::vector<double> >();
}

void BaseBlock::setOption(IContext *context, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    std::list<std::string>::iterator iter = std::find(this->options.begin(), this->options.end(), name);

    if (iter != this->options.end())
    {
        //we found it!
        context->setStoredValue(this->getId(), name, value);
    }
}

const std::map<std::string, boost::shared_ptr<IBlockInput> >& BaseBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> >& BaseBlock::getOutputs()
{
    return this->outputs;
}

bool BaseBlock::connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite)
{
    //do we have this output?
    if (this->outputs.count(outputName))
    {
        boost::shared_ptr<IBlockOutput> output = this->outputs.at(outputName);
        //does the other block have the required input?
        if (block->getInputs().count(inputName))
        {
            boost::shared_ptr<IBlockInput> input = block->getInputs().at(inputName);
            if (input->isAttached() && !overwrite)
                return false; //we don't overwrite attached inputs

            output->attachInput(input); //attach the input
        }
    }

    return false; //we failed to connect this for one reason or another
}

boost::shared_ptr<IBlockInput> BaseBlock::addInput(const std::string &name)
{
    if (this->inputs.count(name))
        return boost::shared_ptr<IBlockInput>();

    boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this->getId(), name));

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

    boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this->getId(), name));

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
