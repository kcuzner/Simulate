#include "model.h"

#include "defaultblockfactory.h"
#include "entryblock.h"
#include "exitblock.h"
#include "modelblock.h"

Model::Model(boost::shared_ptr<IBlockFactory> factory)
{
    this->factory = factory;
}

bool Model::addEntry(const std::string &name)
{
    if (this->entries.count(name))
        return false;

    boost::shared_ptr<IEntryBlock> entry(new EntryBlock(this->getNextId(), name));

    this->entries[name] = entry;
    this->blocks[entry->getId()] = entry;

    this->sigBlockAdded(entry);
    this->sigEntryAdded(entry);

    return true;
}

bool Model::removeEntry(const std::string &name)
{
    if (this->entries.count(name))
    {
        boost::shared_ptr<IEntryBlock> entry = this->entries[name];
        this->entries.erase(name);
        this->blocks.erase(entry->getId());

        this->sigBlockRemoved(entry);
        this->sigEntryRemoved(entry);

        return true;
    }

    return false;
}

const std::map<std::string, boost::shared_ptr<IEntryBlock> > &Model::getEntries()
{
    return this->entries;
}

bool Model::addExit(const std::string &name)
{
    if (this->exits.count(name))
        return false;

    boost::shared_ptr<IExitBlock> exit(new ExitBlock(this->getNextId(), name));

    this->exits[name] = exit;
    this->blocks[exit->getId()] = exit;

    this->sigBlockAdded(exit);
    this->sigExitAdded(exit);

    return true;
}

bool Model::removeExit(const std::string &name)
{
    if (this->exits.count(name))
    {
        boost::shared_ptr<IExitBlock> exit = this->exits[name];
        this->exits.erase(name);
        this->blocks.erase(exit->getId());

        this->sigBlockRemoved(exit);
        this->sigExitRemoved(exit);

        return true;
    }

    return false;
}

const std::map<std::string, boost::shared_ptr<IExitBlock> > &Model::getExits()
{
    return this->exits;
}

boost::shared_ptr<IBlock> Model::createBlock(const std::string &group, const std::string &name)
{
    boost::shared_ptr<IBlock> block(this->factory->generateBlock(this->getNextId(), group, name));

    this->blocks[block->getId()] = block;

    return block;
}

bool Model::removeBlock(boost::shared_ptr<IBlock> block)
{
    this->blocks.erase(block->getId());
    return true;
}

bool Model::removeBlock(int id)
{
    this->blocks.erase(id);
    return true;
}

boost::shared_ptr<IModelBlock> Model::addModel(boost::shared_ptr<IModel> model)
{
    boost::shared_ptr<IModelBlock> modelBlock(this->factory->generateModelBlock(this->getNextId(), model));

    this->blocks[modelBlock->getId()] = modelBlock;

    return modelBlock;
}

const std::map<int, boost::shared_ptr<IBlock> > &Model::getBlocks()
{
    return this->blocks;
}

boost::shared_ptr<IBlock> Model::getBlock(int blockId)
{
    if (this->blocks.count(blockId))
        return this->blocks[blockId];

    return boost::shared_ptr<IBlock>();
}

long Model::getNextId()
{
    return this->currentId++;
}
