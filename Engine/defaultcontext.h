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

    virtual boost::shared_ptr<std::vector<double> > getInputValue(int blockId, const std::string& name);

    virtual void setOutputValue(int blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    virtual boost::shared_ptr<std::vector<double> > getStoredValue(int blockId, const std::string& name);

    virtual void setStoredValue(int blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value);

    //virtual boost::weak_ptr<IContext> getParent();

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
     * @brief Prepares the context for a step
     */
    void prepare();

    /**
     * @brief Queues the block with the given id for execution
     * @param blockId
     */
    void queueBlock(int blockId);

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
    bool areAllCachedInputsSet(int blockId);

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
    std::map<int, boost::shared_ptr<BlockIOCache> > ioCache;

    //key: block id
    std::queue<int> executionQueue;

    //key: block id
    std::map<int, std::map<std::string, boost::shared_ptr<std::vector<double> > > > storedValues;

    //child contexts
    std::list<boost::shared_ptr<IContext> > childContexts;

    double stepDelta;
    boost::shared_ptr<IModel> model;
};

#endif // DEFAULTCONTEXT_H
