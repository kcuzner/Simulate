#ifndef DEFAULTCONTEXT_H
#define DEFAULTCONTEXT_H

#include <map>

#include "interfaces/iblock.h"
#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"
#include "interfaces/imodel.h"
#include "interfaces/icontext.h"

class DefaultContext : public IContext
{
public:
    DefaultContext(const boost::shared_ptr<IModel>& model);

    virtual void reset();

    virtual boost::shared_ptr<std::vector<double> > getInputValue(IBlock* block, const std::string& name);

    virtual void setOutputValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::shared_ptr<std::vector<double> > getStoredValue(IBlock* block, const std::string& name);

    virtual void setStoredValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::weak_ptr<IContext> getParent();

    virtual boost::shared_ptr<IContext> createChildContext(boost::shared_ptr<IModel>);

    virtual void step();

protected:
    /**
     * @brief Caches the inputs and outputs of the block in preparation for simulation.
     * Resets the values for the inputs as well. This should only be called at the
     * start of a simulation or when the context is constructed.
     * @param block
     */
    void cacheBlockIO(const boost::shared_ptr<IBlock>& block);

    /**
     * @brief Goes through the input pointer cache and removes input values to any dead inputs
     */
    void cleanDeadInputs();

    /**
     * @brief Cache of inputs/outputs for a block created when the simulation starts
     */
    struct BlockIOCache
    {
        std::map<std::string, int> inputs; //value: input uid
        std::map<std::string, boost::weak_ptr<IBlockOutput> > outputs;
    };

    //key: input uid
    std::map<int, std::vector<double> > inputValues;
    std::map<int, boost::weak_ptr<IBlockInput> > inputPointerCache;

    //key: block uid
    std::map<int, boost::shared_ptr<BlockIOCache> > ioCache;

    boost::shared_ptr<IModel> model;
};

#endif // DEFAULTCONTEXT_H
