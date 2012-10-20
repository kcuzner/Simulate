#include "model.h"
#include "entryblock.h"
#include "exitblock.h"

using namespace Simulation;

Model::Model(QObject *parent) :
    QObject(parent)
{
}

QList<Block *> Model::getBlocks()
{
    return this->blocks;
}


Block* Model::addBlock(Block *block)
{
    this->blocks << block;

    emit(this->blockAdded(block));

    return block;
}

EntryBlock* Model::addEntry(QString &name)
{
    EntryBlock* block = new EntryBlock(this, name);

    this->entries[name] = block;
    this->blocks << block;

    emit(this->entryAdded(block));
    emit(this->blockAdded(block));

    return block;
}

ExitBlock* Model::addExit(QString name)
{
    ExitBlock* block = new ExitBlock(this, name);

    this->exits[name] = block;
    this->blocks << block;

    emit(this->exitAdded(block));
    emit(this->blockAdded(block));

    return block;
}

void Model::removeEntry(QString name)
{
    EntryBlock* block = this->entries[name];

    this->removeEntry(block);
}

void Model::removeEntry(EntryBlock *block)
{
    this->entries.remove(block->getName());
    this->blocks.removeAll(block);

    emit(this->blockRemoved(block));
    emit(this->entryRemoved(block));

    delete block;
}

void Model::removeExit(QString name)
{
    ExitBlock* block = this->exits[name];

    this->removeExit(block);
}

void Model::removeExit(ExitBlock *block)
{
    this->exits.remove(block->getName());
    this->blocks.removeAll(block);

    emit(this->blockRemoved(block));
    emit(this->exitRemoved(block));

    delete block;
}
