#ifndef IBLOCKINPUT_H
#define IBLOCKINPUT_H

#include <string>

#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

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

    virtual bool isAttached() = 0;

    /**
     * @brief Sets the output attached to this input to something different
     * @param output
     * @return
     */
    virtual bool setOutput(IBlockOutput* output) = 0;

    /**
     * @brief This signal is sent when the output attached to this is changed.
     * Output blocks should monitor these signals so the input lists are clean.
     * First parameter is sender, Second is output block.
     */
    boost::signals2::signal<void (IBlockInput*, IBlockOutput*)> sigOutputChanged;
};

#endif // IBLOCKINPUT_H
