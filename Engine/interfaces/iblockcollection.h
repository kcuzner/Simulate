#ifndef IBLOCKCOLLECTION_H
#define IBLOCKCOLLECTION_H

#include "iblockfactory.h"

/**
 * @brief IBlockCollections are structures used for factories to have blocks declared to them
 */
class IBlockCollection
{
public:
    virtual ~IBlockCollection() {}

    /**
     * @brief Adds the blocks in this collection to the passed factory
     * @param factory
     */
    virtual void declareToFactory(boost::shared_ptr<IBlockFactory> factory) = 0;
};

#endif // IBLOCKCOLLECTION_H
