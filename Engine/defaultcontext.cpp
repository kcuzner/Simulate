#include "defaultcontext.h"

#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"

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
    std::list<boost::shared_ptr<IContext> >::iterator iter;
    for(iter = this->childContexts.begin(); iter != this->childContexts.end(); iter++)
    {
        (*iter)->setStepDelta(d);
    }
}


void DefaultContext::reset()
{
    std::map<int, boost::shared_ptr<IBlock> > blocks = this->model->getBlocks();

    //cache all the io on eadch block
    std::map<int, boost::shared_ptr<IBlock> >::const_iterator iter;
    for(iter = blocks.begin(); iter != blocks.end(); iter++)
    {
        this->cacheBlockIO((*iter).second);
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

/*boost::weak_ptr<IContext> DefaultContext::getParent()
{
    return this->parent;
}*/

boost::shared_ptr<IContext> DefaultContext::createChildContext(boost::shared_ptr<IModel> model)
{
    boost::shared_ptr<IContext> child(new DefaultContext(this->getStepDelta(), model));

    this->childContexts.push_back(child);

    return child;
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
    this->executionQueue.push(blockId);
}

void DefaultContext::setAttachedInputs(boost::shared_ptr<IBlockOutput> output, boost::shared_ptr<std::vector<double> > value)
{
    //set this output's attached inputs to their values
    std::set<boost::weak_ptr<IBlockInput> > inputs = output->getAttachedInputs();
    std::set<boost::weak_ptr<IBlockInput> >::const_iterator iter;
    for(iter = inputs.begin(); iter != inputs.end(); iter++)
    {
        boost::shared_ptr<IBlockInput> input = (*iter).lock();
        if (input)
        {
            //from the block id of this input, set its spot
            if (this->ioCache.count(input->getBlockId()))
            {
                this->ioCache[input->getBlockId()]->inputValues[input->getName()] = value;
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
