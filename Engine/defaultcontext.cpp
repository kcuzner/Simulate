#include "defaultcontext.h"

#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"

#include <boost/foreach.hpp>

#include <iostream>

DefaultContext::DefaultContext(double stepDelta, const boost::shared_ptr<IModel>& model)
{
    this->stepDelta = stepDelta;
    this->model = model;

    //reset this context to the model
    this->reset();
}

double DefaultContext::getStepDelta()
{
    return this->stepDelta;
}


void DefaultContext::setStepDelta(double d)
{
    this->stepDelta = d;
    std::map<long, boost::shared_ptr<IContext> >::iterator iter;
    for(iter = this->childContexts.begin(); iter != this->childContexts.end(); iter++)
    {
        (*iter).second->setStepDelta(d);
    }
}


void DefaultContext::reset()
{
    std::map<int, boost::shared_ptr<IBlock> > blocks = this->model->getBlocks();

    std::map<int, boost::shared_ptr<IBlock> >::const_iterator iter;
    for(iter = blocks.begin(); iter != blocks.end(); iter++)
    {
        //cache the IO on the block
        this->cacheBlockIO((*iter).second);
        //initialize the block to this context
        (*iter).second->initialize(this);
    }
}

boost::shared_ptr<std::vector<double> > DefaultContext::getInputValue(int blockId, const std::string &name)
{
    //find the block cache
    if (this->ioCache.count(blockId))
    {
        //find the input number
        boost::shared_ptr<BlockIOCache> cache = this->ioCache[blockId];
        if (cache->inputValues.count(name))
        {
            return cache->inputValues[name];
        }
    }

    //if it wasn't found, we fall through to the null pointer
    return boost::shared_ptr<std::vector<double> >();
}

void DefaultContext::setOutputValue(int blockId, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    //find the block cache
    if (this->ioCache.count(blockId))
    {
        //find the output pointer
        boost::shared_ptr<BlockIOCache> cache = this->ioCache[blockId];
        if (cache->outputs.count(name))
        {
            boost::shared_ptr<IBlockOutput> output = cache->outputs[name].lock();
            if (output)
            {
                this->setAttachedInputs(output, value);
            }
        }
    }
}

boost::shared_ptr<std::vector<double> > DefaultContext::getStoredValue(int blockId, const std::string &name)
{
    if (this->storedValues.count(blockId))
    {
        if (this->storedValues[blockId].count(name))
        {
            return this->storedValues[blockId][name];
        }
    }
    return boost::shared_ptr<std::vector<double> >();
}

void DefaultContext::setStoredValue(int blockId, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
    this->storedValues[blockId][name] = value;
}

boost::shared_ptr<IContext> DefaultContext::createChildContext(long blockId, boost::shared_ptr<IModel> model)
{
    boost::shared_ptr<IContext> child(new DefaultContext(this->getStepDelta(), model));

    this->childContexts[blockId] = child;

    return child;
}

boost::shared_ptr<IContext> DefaultContext::getChildContext(long blockId)
{
    if (this->childContexts.count(blockId))
        return this->childContexts[blockId];

    return boost::shared_ptr<IContext>();
}

void DefaultContext::step()
{
    //step 1: prepare the context for stepping
    this->prepare();
    //step 2: run through the execution queue
    while(!this->executionQueue.empty())
    {
        int blockId = this->executionQueue.front();
        boost::shared_ptr<IBlock> block = this->model->getBlock(blockId);
        if (block)
        {
            block->execute(this, this->getStepDelta());
        }
        this->executionQueue.pop(); //finished executing
    }
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries = this->model->getEntries();
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits = this->model->getExits();
    //step 3: Matching entries to the exit blocks should transfer values
    typedef std::pair<std::string, boost::shared_ptr<IExitBlock> > ExitRecord;
    BOOST_FOREACH(ExitRecord record, exits)
    {
        if (entries.count(record.first))
        {
            //there is an entry with this name
            entries[record.first]->setCurrentValue(this, record.second->getCurrentValue(this));
        }
    }
}

void DefaultContext::cacheBlockIO(const boost::shared_ptr<IBlock>& block)
{

    //clean the io cache
    this->ioCache.erase(block->getId());

    boost::shared_ptr<BlockIOCache> cache(new BlockIOCache());
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs = block->getOutputs();

    //save input number
    cache->nInputs = block->getInputs().size();

    //cache the outputs
    std::map<std::string, boost::shared_ptr<IBlockOutput> >::const_iterator iter;
    for(iter = outputs.begin(); iter != outputs.end(); iter++)
    {
        cache->outputs[(*iter).first] = boost::weak_ptr<IBlockOutput>((*iter).second);
    }

    //save the cache
    this->ioCache[block->getId()] = cache;
}

void DefaultContext::prepare()
{
    std::map<int, boost::shared_ptr<BlockIOCache> >::iterator iter;
    for(iter = this->ioCache.begin(); iter != this->ioCache.end(); iter++)
    {
        boost::shared_ptr<BlockIOCache> cache = (*iter).second;
        //step 1: clear all input values
        cache->inputValues.clear();
        //step 2: queue blocks without inputs for exeuction
        if (cache->nInputs == 0)
        {
            //queue this block for execution
            this->queueBlock((*iter).first);
        }
    }
}

void DefaultContext::queueBlock(int blockId)
{
    std::cout << blockId << " queued for execution" << std::endl;
    this->executionQueue.push(blockId);
}

void DefaultContext::setAttachedInputs(boost::shared_ptr<IBlockOutput> output, boost::shared_ptr<std::vector<double> > value)
{
    std::cout << value << std::endl;
    //set this output's attached inputs to their values
    std::vector<boost::shared_ptr<IBlockInput> > inputs = output->getAttachedInputs();
    std::vector<boost::shared_ptr<IBlockInput> >::const_iterator iter;
    for(iter = inputs.begin(); iter != inputs.end(); iter++)
    {
        boost::shared_ptr<IBlockInput> input = (*iter);
        if (input)
        {
            //from the block id of this input, set its spot
            if (this->ioCache.count(input->getBlockId()))
            {
                this->ioCache[input->getBlockId()]->inputValues[input->getName()] = value;

                //if all the cached inputs are set we queue this for execution
                if (this->areAllCachedInputsSet(input->getBlockId()))
                {
                    this->queueBlock(input->getBlockId());
                }
            }
        }
    }
}

bool DefaultContext::areAllCachedInputsSet(int blockId)
{
    //if is no cache, this block has all its cached inputs set since there are no cached inputs
    if (this->ioCache.count(blockId))
    {
        boost::shared_ptr<BlockIOCache> cache = this->ioCache[blockId];
        return cache->nInputs == cache->inputValues.size();
    }
    //if we make it this far, all the inputs have a value
    return true;
}
