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

boost::shared_ptr<std::vector<double> > ExitBlock::getCurrentValue(IContext *context)
{
    return context->getStoredValue(this->getId(), "Value");
}

std::string ExitBlock::getExitName()
{
    return this->name;
}

