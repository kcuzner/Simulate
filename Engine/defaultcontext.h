#ifndef DEFAULTCONTEXT_H
#define DEFAULTCONTEXT_H

#include <map>

#include "interfaces/iblock.h"
#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"
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
    /**
     * @brief Caches the inputs and outputs of the block in preparation for simulation
     * @param block
     */
    void cacheBlockIO(boost::shared_ptr<IBlock> block);


    struct BlockIOCache
    {
        std::map<std::string, boost::weak_ptr<IBlockInput> > inputs;
        std::map<std::string, boost::weak_ptr<IBlockOutput> > outputs;
    };

    std::map<IBlock*, boost::shared_ptr<BlockIOCache> > ioCache;

    std::map<boost::weak_ptr<IBlockInput>, std::vector<double> > currentInputValues;
};

#endif // DEFAULTCONTEXT_H
