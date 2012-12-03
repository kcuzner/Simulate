#include "defaultcontext.h"

DefaultContext::DefaultContext()
{
}

void DefaultContext::reset()
{
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

boost::shared_ptr<IContext> DefaultContext::createChildContext()
{
}

void DefaultContext::step(boost::shared_ptr<IModel> model)
{
}

void DefaultContext::cacheBlockIO(boost::shared_ptr<IBlock> block)
{
}
