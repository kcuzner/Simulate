#ifndef IBLOCKOUTPUT_H
#define IBLOCKOUTPUT_H

#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "iblockio.h"

class IBlockInput;

/**
 * @brief Output from a block
 * Inputs and outputs define the network of connections between blocks and are
 * used internally by the blocks to reference eachother.
 */
class IBlockOutput : public IBlockIO
{
public:
    virtual ~IBlockOutput() {}

    /**
     * @brief Returns all inputs that are attached to this output
     * @return
     */
    virtual const std::vector<boost::shared_ptr<IBlockInput> > &getAttachedInputs() = 0;

    /**
     * @brief Detaches all inputs from this output
     */
    virtual void detachAllInputs() = 0;

    /**
     * @brief Attaches the passed input to this output
     * @param input
     * @return True if newly attached
     */
    virtual bool attachInput(boost::shared_ptr<IBlockInput> input) = 0;

    /**
     * @brief Detaches the passed input from this output
     * @param input
     * @return True if newly detached
     */
    virtual bool detachInput(boost::shared_ptr<IBlockInput> input) = 0;

    boost::signals2::signal<void (boost::shared_ptr<IBlockInput>)> sigInputAttached;
    boost::signals2::signal<void (boost::shared_ptr<IBlockInput>)> sigInputDetached;
};

#endif // IBLOCKOUTPUT_H
