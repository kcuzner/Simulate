#ifndef IBLOCKIO_H
#define IBLOCKIO_H

#include <string>

#include <boost/smart_ptr.hpp>

class IBlock;

/**
 * @brief Base interface for block io classes
 */
class IBlockIO
{
public:
    virtual ~IBlockIO() {}

    /**
     * @brief Returns the ID of the block this io is attached to
     * @return block id
     */
    virtual long getBlockId() = 0;

    virtual std::string getName() = 0;

    virtual bool isSiblingOf(boost::weak_ptr<IBlockIO> io) = 0;
};

#endif // IBLOCKIO_H
