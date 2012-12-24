#include "entryblock.h"

#include "baseblockoutput.h"

#define ENTRYBLOCK_OUTPUT_NAME "Output"

EntryBlock::EntryBlock(long id, std::string name)
{
    this->id = id;
    this->name = name;

    this->options.clear();
    this->options.push_back(IENTRYBLOCK_OPTION_NAME);

    boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this->getId(), ENTRYBLOCK_OUTPUT_NAME));
    this->outputs[ENTRYBLOCK_OUTPUT_NAME] = output;
}

long EntryBlock::getId()
{
    return this->id;
}

std::string EntryBlock::getGroup()
{
    return "engine";
}

std::string EntryBlock::getName()
{
    return "entry";
}

const std::list<std::string> &EntryBlock::getOptionNames()
{
    return this->options;
}

boost::shared_ptr<std::vector<double> > EntryBlock::getOption(IContext *context, const std::string &name)
{
    if (name != IENTRYBLOCK_OPTION_NAME)
        return boost::shared_ptr<std::vector<double> >();

    return this->initialValue;
}

void EntryBlock::setOption(IContext *context, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    if (name == IENTRYBLOCK_OPTION_NAME)
    {
        this->initialValue = value;
    }
}

void EntryBlock::initialize(IContext *context)
{
    context->setStoredValue(this->getId(), "Value", this->initialValue);
}

void EntryBlock::execute(IContext *context, double)
{
    context->setOutputValue(this->getId(), ENTRYBLOCK_OUTPUT_NAME, context->getStoredValue(this->getId(), "Value"));
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &EntryBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &EntryBlock::getOutputs()
{
    return this->outputs;
}

void EntryBlock::setCurrentValue(IContext *context, boost::shared_ptr<std::vector<double> > value)
{
    context->setStoredValue(this->getId(), "Value", value);
}

std::string EntryBlock::getEntryName()
{
    return this->name;
}
