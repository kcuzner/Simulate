 #ifndef SYSTEMBLOCKS_H
#define SYSTEMBLOCKS_H

#include "../interfaces/iblockcollection.h"

namespace System
{
    class SystemBlocks : public IBlockCollection
    {
    public:
        SystemBlocks();

        virtual void declareToFactory(boost::shared_ptr<IBlockFactory> factory);
    };
}

#endif // SYSTEMBLOCKS_H
