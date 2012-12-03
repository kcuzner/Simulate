#ifndef DEFAULTCONTEXT_H
#define DEFAULTCONTEXT_H

#include <map>

#include "interfaces/icontext.h"

class DefaultContext : public IContext
{
public:
    DefaultContext();

    virtual void reset();

    virtual boost::shared_ptr<std::vector<double> > getInputValue(IBlock* block, const std::string& name);

    virtual void setOutputValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::shared_ptr<std::vector<double> > getStoredValue(IBlock* block, const std::string& name);

    virtual void setStoredValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::weak_ptr<IContext> getParent();

    virtual boost::shared_ptr<IContext> createChildContext();

    virtual void step(boost::shared_ptr<IModel> model);

protected:
};

#endif // DEFAULTCONTEXT_H
