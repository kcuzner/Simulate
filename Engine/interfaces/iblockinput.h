#ifndef IBLOCKINPUT_H
#define IBLOCKINPUT_H

#include <string>

#include <boost/smart_ptr.hpp>

#include "iblockio.h"

class IBlockOutput;

/**
 * @brief Input to a block
 * Inputs and outputs define the network of connections between blocks and are
 * used internally by the blocks to reference each other.
 */
class IBlockInput : public IBlockIO
{
public:
    virtual ~IBlockInput() {}

    virtual boost::weak_ptr<IBlockOutput> getAttachedOutput() = 0;

    virtual bool attachOutput(boost::weak_ptr<IBlockOutput> output) = 0;

    virtual bool detachOutput(boost::weak_ptr<IBlockOutput> output) = 0;
};

#endif // IBLOCKINPUT_H
