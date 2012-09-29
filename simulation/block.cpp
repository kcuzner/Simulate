#include "block.h"
#include "input.h"
#include "output.h"

using namespace Simulation;

Block::Block(QObject *parent) :
    QObject(parent)
{
}

Input *Block::addInput(QString name)
{
}

Output *Block::addOutput(QString name)
{
}

void Block::removeInput(QString name)
{
}

void Block::removeInput(Input *input)
{
}

void Block::removeOutput(QString name)
{
}

void Block::removeOutput(Input *input)
{
}
