#include "blockfactory.h"
#include "block.h"

using namespace Simulation;

BlockFactory::BlockFactory()
{
}

BlockFactory *BlockFactory::getInstance()
{
    if (mInstance)
        return mInstance;

    mInstance = new BlockFactory();

    return mInstance;
}

void BlockFactory::declareBlock(QString name, Block* (*generate)())
{
}
