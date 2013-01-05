#include "entryblock.h"

#include <sstream>

#include "baseblockoutput.h"

EntryBlock::EntryBlock(long id, std::string name)
{
    this->id = id;
    this->name = name;

    this->options.clear();
    this->options.push_back(IENTRYBLOCK_OPTION_NAME);

    boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this->getId(), IENTRYBLOCK_OUTPUT_NAME));
    this->outputs[IENTRYBLOCK_OUTPUT_NAME] = output;
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

boost::shared_ptr<std::vector<double> > EntryBlock::getOption(const std::string &name) const
{
    if (name != IENTRYBLOCK_OPTION_NAME)
        return boost::shared_ptr<std::vector<double> >();

    return this->optionValues.at(IENTRYBLOCK_OPTION_NAME);
}

void EntryBlock::setOption(const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    if (name == IENTRYBLOCK_OPTION_NAME)
    {
        this->optionValues[IENTRYBLOCK_OPTION_NAME] = value;
    }
}

const std::map<std::string, boost::shared_ptr<std::vector<double> > > &EntryBlock::getOptions() const
{
    return this->optionValues;
}

bool EntryBlock::initialize(IContext *context, std::string& error)
{
    if (this->optionValues.count(IENTRYBLOCK_OPTION_NAME) == 0)
    {
        //we need an initial value...
        std::stringstream s;
        s << "No initial value specified for EntryBlock " << this->getId() << " (" << this->getEntryName() << ")";
        error = s.str();
        return false;
    }

    //we copy our option into the stored values since later it is set on a per-context basis (setCurrentValue)
    context->setStoredValue(this->getId(), "Value", this->getOption(IENTRYBLOCK_OPTION_NAME));

    return true;
}

void EntryBlock::execute(IContext *context, double)
{
    //note that this is NOT copying the option to the output: it is copying the current value to the output
    context->setOutputValue(this->getId(), IENTRYBLOCK_OUTPUT_NAME, context->getStoredValue(this->getId(), "Value"));
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &EntryBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &EntryBlock::getOutputs()
{
    return this->outputs;
}

bool EntryBlock::connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite)
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

const std::map<std::string, std::string> &EntryBlock::getData()
{
    return this->data;
}

const std::string &EntryBlock::getData(const std::string &key)
{
    return this->data.at(key);
}

void EntryBlock::setData(const std::string &key, const std::string &value)
{
    this->data[key] = value;
}

void EntryBlock::setCurrentValue(IContext *context, boost::shared_ptr<std::vector<double> > value)
{
    context->setStoredValue(this->getId(), "Value", value);
}

std::string EntryBlock::getEntryName()
{
    return this->name;
}
