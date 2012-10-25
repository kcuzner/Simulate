#include "blockfactory.h"
#include "block.h"

using namespace Simulation;
using namespace Interfaces;

BlockFactory* BlockFactory::instance;

BlockFactory *BlockFactory::getInstance()
{
    if (instance)
        return instance;

    instance = new BlockFactory();

    return instance;
}

void BlockFactory::declareBlock(QString name, GenerateBlock generator)
{
    this->blocks[name] = generator;
}

Block *BlockFactory::generateBlock(QString name, Model* model)
{
    return new Block(model, QSharedPointer<IBlockCore>(this->blocks[name](model)));
}

BlockFactory::BlockFactory()
{
}
