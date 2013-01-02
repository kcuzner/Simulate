#include "model.h"

#include "defaultblockfactory.h"
#include "entryblock.h"
#include "exitblock.h"
#include "modelblock.h"

Model::Model(const std::string &name, boost::shared_ptr<IBlockFactory> factory)
{
    this->factory = factory;
    this->currentId = 0; //reset current id

    this->name = name;
}

const std::string &Model::getName()
{
    return this->name;
}

boost::shared_ptr<IEntryBlock> Model::addEntry(const std::string &name)
{
    return this->addEntry(this->getNextId(), name);
}

boost::shared_ptr<IEntryBlock> Model::addEntry(int id, const std::string &name)
{
    if (!this->useId(id))
    {
        //throw an exception?
        return boost::shared_ptr<IEntryBlock>();
    }

    boost::shared_ptr<IEntryBlock> entry(new EntryBlock(id, name));

    this->entries[name] = entry;
    this->blocks[entry->getId()] = entry;

    this->sigBlockAdded(entry);
    this->sigEntryAdded(entry);

    return entry;
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

boost::shared_ptr<IExitBlock> Model::addExit(const std::string &name)
{
    return this->addExit(this->getNextId(), name);
}

boost::shared_ptr<IExitBlock> Model::addExit(int id, const std::string &name)
{
    if (!this->useId(id))
    {
        //throw an exception?
        return boost::shared_ptr<IExitBlock>();
    }

    boost::shared_ptr<IExitBlock> exit(new ExitBlock(id, name));

    this->exits[name] = exit;
    this->blocks[exit->getId()] = exit;

    this->sigBlockAdded(exit);
    this->sigExitAdded(exit);

    return exit;
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
    return this->createBlock(this->getNextId(), group, name);
}

boost::shared_ptr<IBlock> Model::createBlock(int id, const std::string &group, const std::string &name)
{
    if (!this->useId(id))
    {
        //throw an exception?
        return boost::shared_ptr<IBlock>();
    }

    boost::shared_ptr<IBlock> block(this->factory->generateBlock(id, group, name));

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
    return this->addModel(this->getNextId(), model);
}

boost::shared_ptr<IModelBlock> Model::addModel(int id, boost::shared_ptr<IModel> model)
{
    if (!this->useId(id))
    {
        //throw an exception?
        return boost::shared_ptr<IModelBlock>();
    }

    boost::shared_ptr<IModelBlock> modelBlock(this->factory->generateModelBlock(id, model));

    this->blocks[modelBlock->getId()] = modelBlock;
    this->modelBlocks[modelBlock->getId()] = modelBlock;

    return modelBlock;
}

const std::map<int, boost::shared_ptr<IModelBlock> > &Model::getModelBlocks()
{
    return this->modelBlocks;
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

bool Model::useId(long id)
{
    //step 1: is this id in use?
    if (this->blocks.count(id))
        return false;
    //step 2: current id is now this + 1 if we haven't reached it yet
    if (this->currentId <= id)
        this->currentId = id + 1;

    return true;
}


ModelGenerator::ModelGenerator()
{
    name = "default";
}

const std::string &ModelGenerator::getModelTypeName()
{
    return this->name;
}

boost::shared_ptr<IModel> ModelGenerator::generate(const std::string &name, boost::shared_ptr<IBlockFactory> factory)
{
    return boost::shared_ptr<IModel>(new Model(name, factory));
}
