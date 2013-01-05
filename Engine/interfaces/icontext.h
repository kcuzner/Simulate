#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <vector>
#include <string>

#include <boost/smart_ptr.hpp>

class IBlock; //forward declaration of IBlock
class IModel; //forward declaration of IModel

/**
 * @brief Context passed to blocks for computation
 */
class IContext
{
public:
    virtual ~IContext() {}

    /**
     * @brief Returns the step delta for this context
     * @return
     */
    virtual double getStepDelta() = 0;
    /**
     * @brief Sets the step delta for this context and all its children
     * @param d
     */
    virtual void setStepDelta(double d) = 0;

    /**
     * @brief Resets this context to its initial state. Also should initialize all the blocks
     */
    virtual void reset() = 0;

    /**
     * @brief Returns the value of an input for this context
     * @param blockId UID of the block as returned by getUID
     * @param name Name of the input
     * @return Value of the input or a null pointer
     */
    virtual boost::shared_ptr<std::vector<double> > getInputValue(long blockId, const std::string& name) = 0;

    /**
     * @brief Sets the value of an output for the passed context
     * @param blockId UID of the block as returned by getUID
     * @param name Name of the output
     * @param value Value to set the output to
     */
    virtual void setOutputValue(long blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value) = 0;

    /**
     * @brief Returns a stored value in this context
     * @param blockId UID of the block as returned by getUID
     * @param name Name of the value
     * @return The value
     */
    virtual boost::shared_ptr<std::vector<double> > getStoredValue(long blockId, const std::string& name) = 0;

    /**
     * @brief Stores a value in this context
     * @param block Block to store the value for
     * @param name Name of the value
     * @param value Value to set
     */
    virtual void setStoredValue(long blockId, const std::string& name, boost::shared_ptr<std::vector<double> > value) = 0;

    /**
     * @brief Gets an option value for the passed block id. Options should be cached at the beginning of a run (when reset
     * is called) to promote thread safety
     * @param blockId
     * @param name
     * @return
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(long blockId, const std::string& name) = 0;

    /**
     * @brief Creates a child context for a model assigned to a block. This will replace any existing context.
     * @param blockId
     * @param model
     * @return
     */
    virtual boost::shared_ptr<IContext> createChildContext(long blockId, boost::shared_ptr<IModel> model) = 0;

    /**
     * @brief Returns the child context assigned to the block or null of not found
     * @param blockId
     * @return
     */
    virtual boost::shared_ptr<IContext> getChildContext(long blockId) = 0;

    /**
     * @brief Runs a step on the model this context is attached to. This method should return once running has been completed
     * @param model
     */
    virtual void step() = 0;
};

#endif // ICONTEXT_H
