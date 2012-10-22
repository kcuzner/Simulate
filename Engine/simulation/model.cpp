#include "model.h"
#include "entryblock.h"
#include "exitblock.h"

using namespace Simulation;

Model::Model(QObject *parent) :
    QObject(parent)
{
}

QList<QSharedPointer<Block> > Model::getBlocks()
{
    return this->blocks;
}


void Model::addBlock(QSharedPointer<Block> block)
{
    this->blocks << block;

    emit(this->blockAdded(block));
}

QSharedPointer<EntryBlock> Model::addEntry(const QString &name)
{
    QSharedPointer<EntryBlock> block(new EntryBlock(this, name));

    this->entries[name] = block;
    this->blocks << block;

    emit(this->entryAdded(block));
    emit(this->blockAdded(block));

    return block;
}

QSharedPointer<ExitBlock> Model::addExit(const QString &name)
{
    QSharedPointer<ExitBlock> block(new ExitBlock(this, name));

    this->exits[name] = block;
    this->blocks << block;

    emit(this->exitAdded(block));
    emit(this->blockAdded(block));

    return block;
}

void Model::removeEntry(const QString &name)
{
    QSharedPointer<EntryBlock> block = this->entries[name];

    this->entries.remove(name);
    this->blocks.removeAll(block);

    emit(this->blockRemoved(block));
    emit(this->entryRemoved(block));
}

void Model::removeExit(const QString &name)
{
    QSharedPointer<ExitBlock> block = this->exits[name];

    this->exits.remove(block->getName());
    this->blocks.removeAll(block);

    emit(this->blockRemoved(block));
    emit(this->exitRemoved(block));
}
