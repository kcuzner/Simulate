#include "modelblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

#include <boost/foreach.hpp>

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
    return this->optionBlockNames;
}

boost::shared_ptr<std::vector<double> > ModelBlock::getOption(IContext *context, const std::string &name)
{
    //in reality: we store/retrieve this option value in our context and then when we are initialized, we set the option values

    if (this->optionBlocks.count(name))
    {
        return context->getStoredValue(this->getId(), name);
    }

    return boost::shared_ptr<std::vector<double> >(); //return null
}

void ModelBlock::setOption(IContext *context, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    //in reality: we store/retrieve this option value in our context and then when we are initialized, we set the option values

    if (this->optionBlocks.count(name))
    {
        context->setStoredValue(this->getId(), name, value);
    }
}

void ModelBlock::initialize(IContext *context)
{
    boost::shared_ptr<IContext> childContext = context->getChildContext(this->getId());
    if (!childContext)
    {
        //create a new child context
        childContext = context->createChildContext(this->getId(), this->model);
    }

    //reset this since a simulation is about to start
    childContext->reset();

    //set all the initial values for the entry blocks from our context (our options)
    typedef std::pair<std::string, std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > > OptionBlock;
    BOOST_FOREACH( OptionBlock option, this->optionBlocks)
    {
        option.second.first->setOption(childContext.get(), IENTRYBLOCK_OPTION_NAME, context->getStoredValue(this->getId(), option.first));
    }
}

void ModelBlock::execute(IContext *context, double)
{
    /**
     * When executing a model in a child context, the input blocks always have their
     * values tied to the input values of this block and the output blocks are always
     * tied to the outputs of this block. Initial values are only for root level
     * simulations since there is nothing to control the input blocks.
     */
    //get our context
    boost::shared_ptr<IContext> mContext = context->getChildContext(this->getId());

    //set the entry values to our inputs
    typedef std::pair<std::string, boost::shared_ptr<IEntryBlock> > EntryRecord;
    BOOST_FOREACH(EntryRecord entry, this->inputEntryBlocks)
    {
        entry.second->setCurrentValue(mContext.get(), context->getInputValue(this->getId(), entry.first));
    }

    //execute the step
    mContext->step();

    //set the current option values
    typedef std::pair<std::string, std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > > OptionBlock;
    BOOST_FOREACH(OptionBlock option, this->optionBlocks)
    {
        option.second.first->setCurrentValue(mContext.get(), option.second.second->getCurrentValue(mContext.get()));
    }

    //set our outputs to the exit block values
    typedef std::pair<std::string, boost::shared_ptr<IExitBlock> > ExitRecord;
    BOOST_FOREACH(ExitRecord record, this->outputExitBlocks)
    {
        context->setOutputValue(this->getId(), record.first, record.second->getCurrentValue(mContext.get()));
    }
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ModelBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ModelBlock::getOutputs()
{
    return this->outputs;
}

bool ModelBlock::connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite)
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

boost::shared_ptr<IModel> ModelBlock::getModel()
{
    return this->model;
}

boost::shared_ptr<IContext> ModelBlock::getContext(IContext *context)
{
    boost::shared_ptr<IContext> childContext = context->getChildContext(this->getId());

    if (!childContext)
    {
        childContext = context->createChildContext(this->getId(), this->model);
    }

    return childContext;
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
