#include "defaultcontext.h"

#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"

DefaultContext::DefaultContext(const boost::shared_ptr<IModel>& model)
{
    this->model = model;

    //reset this context to the model
    this->reset();
}

void DefaultContext::reset()
{
    std::map<int, boost::shared_ptr<IBlock> > blocks = this->model->getBlocks();

    std::map<int, boost::shared_ptr<IBlock> >::const_iterator iter;
    for(iter = blocks.begin(); iter != blocks.end(); iter++)
    {
        this->cacheBlockIO((*iter).second);
    }
}

boost::shared_ptr<std::vector<double> > DefaultContext::getInputValue(IBlock *block, const std::string &name)
{
}

void DefaultContext::setOutputValue(IBlock *block, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
}

boost::shared_ptr<std::vector<double> > DefaultContext::getStoredValue(IBlock *block, const std::string &name)
{
}

void DefaultContext::setStoredValue(IBlock *block, const std::string &name, boost::shared_ptr<std::vector<double> > value)
{
}

boost::weak_ptr<IContext> DefaultContext::getParent()
{
}

boost::shared_ptr<IContext> DefaultContext::createChildContext(boost::shared_ptr<IModel>)
{
}

void DefaultContext::step()
{
}

void DefaultContext::cacheBlockIO(const boost::shared_ptr<IBlock>& block)
{

    //clean the io cache
    if (this->ioCache.count(block->getUID()))
    {
        boost::shared_ptr<BlockIOCache> cache = this->ioCache[block->getUID()];
        std::map<std::string, int>::iterator iter;
        for(iter = cache->inputs.begin(); iter != cache->inputs.end(); iter++)
        {
            this->inputValues.erase((*iter).second);
            this->inputPointerCache.erase((*iter).second);
        }
        this->ioCache.erase(block->getUID());
    }

    boost::shared_ptr<BlockIOCache> cache(new BlockIOCache());
    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs = block->getInputs();
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs = block->getOutputs();

    //cache the inputs
    std::map<std::string, boost::shared_ptr<IBlockInput> >::const_iterator iIter;
    for(iIter = inputs.begin(); iIter != inputs.end(); iIter++)
    {
        boost::shared_ptr<IBlockInput> input = (*iIter).second;
        cache->inputs[(*iIter).first] = input->getUID();
    }

    //cache the outputs
    std::map<std::string, boost::shared_ptr<IBlockOutput> >::const_iterator oIter;
    for(oIter = outputs.begin(); oIter != outputs.end(); oIter++)
    {
    }
}

void DefaultContext::cleanDeadInputs()
{
}
