#include "blockfactory.h"
#include "block.h"

using namespace Simulation;

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
    return new Block(model, this->blocks[name](model));
}

BlockFactory::BlockFactory()
{
}
