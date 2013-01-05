#include "exitblock.h"

#include "baseblockinput.h"

#include <iostream>

ExitBlock::ExitBlock(long id, std::string name)
{
    this->id = id;
    this->name = name;

    boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this->getId(), IEXITBLOCK_INPUT_NAME));
    this->inputs[IEXITBLOCK_INPUT_NAME] = input;
}

long ExitBlock::getId()
{
    return this->id;
}

std::string ExitBlock::getGroup()
{
    return "engine";
}

std::string ExitBlock::getName()
{
    return "exit";
}

const std::list<std::string> &ExitBlock::getOptionNames()
{
    return this->options;
}

boost::shared_ptr<std::vector<double> > ExitBlock::getOption(const std::string &) const
{
    return boost::shared_ptr<std::vector<double> >();
}

void ExitBlock::setOption(const std::string &, boost::shared_ptr<std::vector<double> >)
{
    //do nothing
}

const std::map<std::string, boost::shared_ptr<std::vector<double> > > &ExitBlock::getOptions() const
{
    return this->optionValues;
}

bool ExitBlock::initialize(IContext *, std::string&)
{
    //do nothing
    return true;
}

void ExitBlock::execute(IContext *context, double)
{
    //this stored value is used later in getCurrentValue
    context->setStoredValue(this->getId(), "Value", context->getInputValue(this->getId(), IEXITBLOCK_INPUT_NAME));
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ExitBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ExitBlock::getOutputs()
{
    return this->outputs;
}

bool ExitBlock::connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite)
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

            return true;
        }
    }

    return false; //we failed to connect this for one reason or another
}

const std::map<std::string, std::string> &ExitBlock::getData()
{
    return this->data;
}

const std::string &ExitBlock::getData(const std::string &key)
{
    return this->data.at(key);
}

void ExitBlock::setData(const std::string &key, const std::string &value)
{
    this->data[key] = value;
}

boost::shared_ptr<std::vector<double> > ExitBlock::getCurrentValue(IContext *context)
{
    return context->getStoredValue(this->getId(), "Value");
}

std::string ExitBlock::getExitName()
{
    return this->name;
}

