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
     * @brief Resets this context to a cleared state
     */
    virtual void reset() = 0;

    /**
     * @brief Returns the value of an input for this context
     * @param block Block the input belongs to
     * @param name Name of the input
     * @return Value of the input or a null pointer
     */
    virtual boost::shared_ptr<std::vector<double> > getInputValue(IBlock* block, const std::string& name) = 0;

    /**
     * @brief Sets the value of an output for the passed context
     * @param block Block the output belongs to
     * @param name Name of the output
     * @param value Value to set the output to
     */
    virtual void setOutputValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value) = 0;

    /**
     * @brief Returns a stored value in this context
     * @param block Block to retreive the stored value for
     * @param name Name of the value
     * @return The value
     */
    virtual boost::shared_ptr<std::vector<double> > getStoredValue(IBlock* block, const std::string& name) = 0;

    /**
     * @brief Stores a value in this context
     * @param block Block to store the value for
     * @param name Name of the value
     * @param value Value to set
     */
    virtual void setStoredValue(IBlock* block, const std::string& name, boost::shared_ptr<std::vector<double> > value) = 0;

    /**
     * @brief Gets the parent context of this child context.
     * @return Parent context
     */
    virtual boost::weak_ptr<IContext> getParent() = 0;

    /**
     * @brief Creates a child context of this context
     * @return
     */
    virtual boost::shared_ptr<IContext> createChildContext() = 0;

    /**
     * @brief Runs a step on a model using this context. This method should return once running has been completed
     * @param model
     */
    virtual void step(boost::shared_ptr<IModel> model) = 0;
};

#endif // ICONTEXT_H
