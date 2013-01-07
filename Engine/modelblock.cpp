#include "modelblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

#include <boost/foreach.hpp>

#include <algorithm>
#include <iostream>

ModelBlock::ModelBlock(long id, boost::shared_ptr<IModel> model)
{
    this->id = id;
    this->model = model;

    model->sigEntryAdded.connect(boost::bind(&ModelBlock::entryAdded, this, _1, _2));
    model->sigEntryRemoved.connect(boost::bind(&ModelBlock::entryRemoved, this, _1, _2));
    model->sigExitAdded.connect(boost::bind(&ModelBlock::exitAdded, this, _1, _2));
    model->sigExitRemoved.connect(boost::bind(&ModelBlock::exitRemoved, this, _1, _2));

    //inspect the entries and exits
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries = model->getEntries();
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits = model->getExits();

    std::map<std::string, boost::shared_ptr<IEntryBlock> >::iterator enIter;
    for(enIter = entries.begin(); enIter != entries.end(); enIter++)
    {
        this->entryAdded(model.get(), (*enIter).second);
    }
    std::map<std::string, boost::shared_ptr<IExitBlock> >::iterator exIter;
    for(exIter = exits.begin(); exIter != exits.end(); exIter++)
    {
        this->exitAdded(model.get(), (*exIter).second);
    }
}

long ModelBlock::getId() const
{
    return this->id;
}

std::string ModelBlock::getGroup() const
{
    return "engine";
}

std::string ModelBlock::getName() const
{
    return "model";
}

const std::list<std::string> &ModelBlock::getOptionNames() const
{
    return this->optionBlockNames; //this should be empty
}

boost::shared_ptr<std::vector<double> > ModelBlock::getOption(const std::string &) const
{
    //in reality: we store/retrieve this option value in our context and then when we are initialized, we set the option values

    /*if (this->optionBlocks.count(name) && this->optionValues.count(name))
    {
        return this->optionValues.at(name);
    }*/

    return boost::shared_ptr<std::vector<double> >(); //return null
}

void ModelBlock::setOption(const std::string &, boost::shared_ptr<std::vector<double> >)
{
    //in reality: we store/retrieve this option value in our context and then when we are initialized, we set the option values

    /*if (this->optionBlocks.count(name))
    {
        this->optionValues[name] = value;
    }*/
}

const std::map<std::string, boost::shared_ptr<std::vector<double> > > &ModelBlock::getOptions() const
{
    return this->optionValues;
}

bool ModelBlock::initialize(IContext *context, std::string &)
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
    /*typedef std::pair<std::string, std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > > OptionBlock;
    BOOST_FOREACH( OptionBlock option, this->optionBlocks)
    {
        option.second.first->setOption(childContext.get(), IENTRYBLOCK_OPTION_NAME, context->getStoredValue(this->getId(), option.first));
    }*/

    return true;
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

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ModelBlock::getInputs() const
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ModelBlock::getOutputs() const
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

            this->sigConnected(this, outputName, block, inputName);
            this->sigBlockChanged(this);

            return true;
        }
    }

    return false; //we failed to connect this for one reason or another
}

const std::map<std::string, std::string> &ModelBlock::getData() const
{
    return this->data;
}

const std::string &ModelBlock::getData(const std::string &key) const
{
    return this->data.at(key);
}

void ModelBlock::setData(const std::string &key, const std::string &value)
{
    this->data[key] = value;
    this->sigDataChanged(this, key);
    this->sigBlockChanged(this);
}

boost::shared_ptr<IModel> ModelBlock::getModel() const
{
    return this->model;
}

boost::shared_ptr<IContext> ModelBlock::getContext(IContext *context) const
{
    boost::shared_ptr<IContext> childContext = context->getChildContext(this->getId());

    if (!childContext)
    {
        childContext = context->createChildContext(this->getId(), this->model);
    }

    return childContext;
}

void ModelBlock::entryAdded(IModel *, boost::shared_ptr<IEntryBlock> entry)
{
    std::cout << "entry adding " << entry->getEntryName() << std::endl;
    //do we have any exits matching the name of this entry?
    if (this->outputExitBlocks.count(entry->getEntryName()))
    {
        std::cout << "added option " << entry->getEntryName() << std::endl;
        //remove the exit and its output
        boost::shared_ptr<IExitBlock> exit = this->outputExitBlocks[entry->getEntryName()];
        this->outputExitBlocks.erase(entry->getEntryName());
        boost::shared_ptr<IBlockOutput> output = this->outputs[entry->getEntryName()];
        this->outputs.erase(entry->getEntryName());

        //signal that an output was removed
        this->sigOutputRemoved(this, output);

        //create a pair
        this->optionBlocks[entry->getEntryName()] = std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> >(entry, exit);
        //this->optionBlockNames.push_back(entry->getEntryName()); //create an option
    }
    else
    {
        //add an input to match this entry
        boost::shared_ptr<BaseBlockInput> input(new BaseBlockInput(this->getId(), entry->getEntryName()));
        this->inputs[entry->getEntryName()] = input;

        this->inputEntryBlocks[entry->getEntryName()] = entry;

        //signal than an input was added
        this->sigInputAdded(this, input);
    }

    this->sigBlockChanged(this);
}

void ModelBlock::entryRemoved(IModel *, boost::shared_ptr<IEntryBlock> entry)
{
    //do we have any pairs with this name?
    if (this->optionBlocks.count(entry->getEntryName()))
    {
        //create an output from this pair
        std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > option = this->optionBlocks[entry->getEntryName()];
        //std::list<std::string>::iterator iter = std::find(this->optionBlockNames.begin(), this->optionBlockNames.end(), entry->getEntryName());
        //this->optionBlockNames.erase(iter);
        this->optionBlocks.erase(entry->getEntryName());

        //add an output for the exit block
        boost::shared_ptr<IBlockOutput> output(new BaseBlockOutput(this->getId(), option.second->getExitName()));
        this->outputs[option.second->getExitName()] = output;
        this->outputExitBlocks[option.second->getExitName()] = option.second;

        this->sigOutputAdded(this, output);
    }
    else
    {
        //remove the input for this entry
        boost::shared_ptr<IBlockInput> input = this->inputs[entry->getEntryName()];
        this->inputs.erase(entry->getEntryName());
        this->inputEntryBlocks.erase(entry->getEntryName());

        this->sigInputRemoved(this, input);
    }

    this->sigBlockChanged(this);
}

void ModelBlock::exitAdded(IModel *, boost::shared_ptr<IExitBlock> exit)
{
    std::cout << "exit adding " << exit->getExitName() << std::endl;
    //do we have any entries matching the name of this exit?
    if (this->inputEntryBlocks.count(exit->getExitName()))
    {
        std::cout << "creating option " << exit->getExitName() << std::endl;
        //remove the entry and its input
        boost::shared_ptr<IEntryBlock> entry = this->inputEntryBlocks[exit->getExitName()];
        this->inputEntryBlocks.erase(exit->getExitName());
        boost::shared_ptr<IBlockInput> input = this->inputs[exit->getExitName()];
        this->inputs.erase(exit->getExitName());

        //signal that an input was removed
        this->sigInputRemoved(this, input);

        //create a pair
        this->optionBlocks[exit->getExitName()] = std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> >(entry, exit);
        //this->optionBlockNames.push_back(exit->getExitName());
    }
    else
    {
        //add an output to match this exit
        boost::shared_ptr<BaseBlockOutput> output(new BaseBlockOutput(this->getId(), exit->getExitName()));
        this->outputs[exit->getExitName()] = output;

        this->outputExitBlocks[exit->getExitName()] = exit;

        //signal than an input was added
        this->sigOutputAdded(this, output);
    }

    this->sigBlockChanged(this);
}

void ModelBlock::exitRemoved(IModel *, boost::shared_ptr<IExitBlock> exit)
{
    //do we have any pairs with this name?
    if (this->optionBlocks.count(exit->getExitName()))
    {
        //create an input from this pair
        std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > option = this->optionBlocks[exit->getExitName()];
        //std::list<std::string>::iterator iter = std::find(this->optionBlockNames.begin(), this->optionBlockNames.end(), exit->getExitName());
        //this->optionBlockNames.erase(iter);
        this->optionBlocks.erase(exit->getExitName());

        //add an input for the entry block
        boost::shared_ptr<IBlockInput> input(new BaseBlockInput(this->getId(), option.first->getEntryName()));
        this->inputs[option.first->getEntryName()] = input;
        this->inputEntryBlocks[option.first->getEntryName()] = option.first;

        this->sigInputAdded(this, input);
    }
    else
    {
        //remove the output for this exit
        boost::shared_ptr<IBlockOutput> output = this->outputs[exit->getExitName()];
        this->outputs.erase(exit->getExitName());

        this->outputExitBlocks.erase(exit->getExitName());

        this->sigOutputRemoved(this, output);
    }

    this->sigBlockChanged(this);
}
