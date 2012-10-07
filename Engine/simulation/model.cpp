#include "model.h"

using namespace Simulation;

Model::Model(QObject *parent) :
    QObject(parent)
{
}

QList<Block *> Model::getBlocks()
{
    return this->blocks;
}


void Model::addBlock(Block *block)
{
    this->blocks << block;

    emit(this->blockAdded(block));
}
