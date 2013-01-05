#ifndef DEFAULTCONTEXT_H
#define DEFAULTCONTEXT_H

#include <map>
#include <queue>

#include "interfaces/iblock.h"
#include "interfaces/iblockinput.h"
#include "interfaces/iblockoutput.h"
#include "interfaces/imodel.h"
#include "interfaces/icontext.h"

class DefaultContext : public IContext
{
public:
    DefaultContext(double stepDelta, const boost::shared_ptr<IModel>& model);

    virtual double getStepDelta();

    virtual void setStepDelta(double d);

    virtual void reset();

    virtual boost::shared_ptr<std::vector<double> > getInputValue(long blockId, const std::string& name);

    virtual void setOutputValue(long blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::shared_ptr<std::vector<double> > getStoredValue(long blockId, const std::string& name);

    virtual void setStoredValue(long blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::shared_ptr<std::vector<double> > getOption(long blockId, const std::string &name);

    virtual boost::shared_ptr<IContext> createChildContext(long blockId, boost::shared_ptr<IModel>);

    virtual boost::shared_ptr<IContext> getChildContext(long blockId);

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
     * @brief Caches the options for the passed block in preparation for simulation.
     * This should only be called at the start of a simulation or when the context
     * is constructed;
     * @param block
     */
    void cacheBlockOptions(const boost::shared_ptr<IBlock>& block);

    /**
     * @brief Prepares the context for a step
     */
    void prepare();

    /**
     * @brief Queues the block with the given id for execution
     * @param blockId
     */
    void queueBlock(long blockId);

    /**
     * @brief Sets the inputs attached to the passed output to the given value
     * @param output
     * @param value
     */
    void setAttachedInputs(boost::shared_ptr<IBlockOutput> output, boost::shared_ptr<std::vector<double> > value);

    /**
     * @brief Returns whether or not all inputs recorded for this block have values attached
     * @param blockId
     * @return
     */
    bool areAllCachedInputsSet(long blockId);

    /**
     * @brief Cache of inputs/outputs for a block created when the simulation starts
     */
    struct BlockIOCache
    {
        unsigned int nInputs; //number of inputs
        std::map<std::string, boost::shared_ptr<std::vector<double> > > inputValues; //input values sorted by name
        std::map<std::string, boost::weak_ptr<IBlockOutput> > outputs; //output pointers sorted by name
    };

    //key: block id
    std::map<long, boost::shared_ptr<BlockIOCache> > ioCache;

    //key: block id
    std::queue<long> executionQueue;

    //key: block id
    std::map<long, std::map<std::string, boost::shared_ptr<std::vector<double> > > > storedValues;

    //key: block id
    std::map<long, std::map<std::string, boost::shared_ptr<std::vector<double> > > > optionValues;

    //child contexts. key: block id
    std::map<long, boost::shared_ptr<IContext> > childContexts;

    double stepDelta;
    boost::shared_ptr<IModel> model;
};

#endif // DEFAULTCONTEXT_H
