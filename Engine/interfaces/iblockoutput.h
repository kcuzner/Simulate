#ifndef IBLOCKOUTPUT_H
#define IBLOCKOUTPUT_H

#include <set>
#include <boost/smart_ptr.hpp>

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

    virtual const std::set<boost::weak_ptr<IBlockInput> > &getAttachedInputs() = 0;

    virtual bool attachInput(boost::weak_ptr<IBlockInput> input) = 0;

    virtual bool detachInput(boost::weak_ptr<IBlockInput> input) = 0;
};

#endif // IBLOCKOUTPUT_H
