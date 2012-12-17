#include "modelblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

ModelBlock::ModelBlock(long id, boost::shared_ptr<IModel> model)
{
    this->id = id;
    this->model = model;

    model->sigEntryAdded.connect(boost::bind(&ModelBlock::entryAdded, this, _1));
    model->sigEntryRemoved.connect(boost::bind(&ModelBlock::entryRemoved, this, _1));
    model->sigExitAdded.connect(boost::bind(&ModelBlock::exitAdded, this, _1));
    model->sigExitRemoved.connect(boost::bind(&ModelBlock::exitRemoved, this, _1));

    //inspect the entries and exits
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries = model->getEntries();
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits = model->getExits();

    std::map<std::string, boost::shared_ptr<IEntryBlock> >::iterator enIter;
    for(enIter = entries.begin(); enIter != entries.end(); enIter++)
    {
        this->entryAdded((*enIter).second);
    }
    std::map<std::string, boost::shared_ptr<IExitBlock> >::iterator exIter;
    for(exIter = exits.begin(); exIter != exits.end(); exIter++)
    {
        this->exitAdded((*exIter).second);
    }
}

long ModelBlock::getId()
{
    return this->id;
}

std::string ModelBlock::getGroup()
{
    return "engine";
}

std::string ModelBlock::getName()
{
    return "model";
}

const std::list<std::string> &ModelBlock::getOptionNames()
{
}

const std::vector<double>& ModelBlock::getOption(const std::string &name)
{
}

void ModelBlock::setOption(const std::string &name, const std::vector<double>& value)
{
}

void ModelBlock::initialize(IContext *context)
{
    //create a child context for our model
    context->createChildContext(this->getId(), this->model);
}

void ModelBlock::execute(IContext *context, double delta)
{
    /**
     * When executing a model in a child context, the input blocks always have their
     * values tied to the input values of this block and the output blocks are always
     * tied to the outputs of this block. Initial values are only for root level
     * simulations since there is nothing to control the input blocks.
     */
    //get our context
    boost::shared_ptr<IContext> mContext = context->getChildContext(this->getId());
    //set the current values of the inputs to the context

    //execute the step
    mContext->step();
    //syncronize our outputs
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ModelBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ModelBlock::getOutputs()
{
    return this->outputs;
}

boost::shared_ptr<IModel> ModelBlock::getModel()
{
    return this->model;
}

void ModelBlock::entryAdded(boost::shared_ptr<IEntryBlock> entry)
{
    //do we have any exits matching the name of this entry?
    if (this->outputExitBlocks.count(entry->getEntryName()))
    {
        //remove the exit and its output
        boost::shared_ptr<IExitBlock> exit = this->outputExitBlocks[entry->getEntryName()];
        this->outputExitBlocks.erase(entry->getEntryName());
        boost::shared_ptr<IBlockOutput> output = this->outputs[entry->getEntryName()];
        this->outputs.erase(entry->getEntryName());

        //signal that an output was removed
        this->sigOutputRemoved(output);

        //create a pair
        this->optionBlocks[entry->getEntryName()] = std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> >(entry, exit);
    }
    else
    {
        //add an input to match this entry
        boost::shared_ptr<BaseBlockInput> input(new BaseBlockInput(this->getId(), entry->getEntryName()));
        this->inputs[entry->getEntryName()] = input;

        //signal than an input was added
        this->sigInputAdded(input);
    }
}

void ModelBlock::entryRemoved(boost::shared_ptr<IEntryBlock> entry)
{
    //do we have any pairs with this name?
    if (this->optionBlocks.count(entry->getEntryName()))
    {
        //create an output from this pair
        std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > option = this->optionBlocks[entry->getEntryName()];
        this->optionBlocks.erase(entry->getEntryName());

        //add an output for the exit block
        boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this->getId(), option.second->getExitName()));
        this->outputs[option.second->getExitName()] = output;
        this->outputExitBlocks[option.second->getExitName()] = option.second;

        this->sigOutputAdded(output);
    }
    else
    {
        //remove the input for this entry
        boost::shared_ptr<IBlockInput> input = this->inputs[entry->getEntryName()];
        this->inputs.erase(entry->getEntryName());

        this->sigInputRemoved(input);
    }
}

void ModelBlock::exitAdded(boost::shared_ptr<IExitBlock> exit)
{
    //do we have any entries matching the name of this exit?
    if (this->inputEntryBlocks.count(exit->getExitName()))
    {
        //remove the entry and its input
        boost::shared_ptr<IEntryBlock> entry = this->inputEntryBlocks[exit->getExitName()];
        this->inputEntryBlocks.erase(exit->getExitName());
        boost::shared_ptr<IBlockInput> input = this->inputs[exit->getExitName()];
        this->inputs.erase(exit->getExitName());

        //signal that an input was removed
        this->sigInputRemoved(input);

        //create a pair
        this->optionBlocks[exit->getExitName()] = std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> >(entry, exit);
    }
    else
    {
        //add an output to match this exit
        boost::shared_ptr<BaseBlockOutput> output(new BaseBlockOutput(this->getId(), exit->getExitName()));
        this->outputs[exit->getExitName()] = output;

        //signal than an input was added
        this->sigOutputAdded(output);
    }
}

void ModelBlock::exitRemoved(boost::shared_ptr<IExitBlock> exit)
{
    //do we have any pairs with this name?
    if (this->optionBlocks.count(exit->getExitName()))
    {
        //create an output from this pair
        std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > option = this->optionBlocks[exit->getExitName()];
        this->optionBlocks.erase(exit->getExitName());

        //add an output for the entry block
        boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this->getId(), option.first->getEntryName()));
        this->inputs[option.first->getEntryName()] = input;
        this->inputEntryBlocks[option.first->getEntryName()] = option.first;

        this->sigInputAdded(input);
    }
    else
    {
        //remove the output for this exit
        boost::shared_ptr<IBlockOutput> output = this->outputs[exit->getExitName()];
        this->outputs.erase(exit->getExitName());

        this->sigOutputRemoved(output);
    }
}
