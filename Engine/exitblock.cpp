#include "exitblock.h"

#include "baseblockinput.h"

#define EXITBLOCK_INPUT_NAME "Input"

ExitBlock::ExitBlock(long id, std::string name)
{
    this->id = id;
    this->name = name;

    boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this->getId(), EXITBLOCK_INPUT_NAME));
    this->inputs[EXITBLOCK_INPUT_NAME] = input;
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

boost::shared_ptr<std::vector<double> > ExitBlock::getOption(IContext *, const std::string &)
{
    return boost::shared_ptr<std::vector<double> >();
}

void ExitBlock::setOption(IContext *, const std::string &, boost::shared_ptr<std::vector<double> >)
{
    //do nothing
}

void ExitBlock::initialize(IContext *)
{
    //do nothing
}

void ExitBlock::execute(IContext *context, double)
{
    context->setStoredValue(this->getId(), "Value", context->getInputValue(this->getId(), EXITBLOCK_INPUT_NAME));
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
        }
    }

    return false; //we failed to connect this for one reason or another
}

boost::shared_ptr<std::vector<double> > ExitBlock::getCurrentValue(IContext *context)
{
    return context->getStoredValue(this->getId(), "Value");
}

std::string ExitBlock::getExitName()
{
    return this->name;
}

