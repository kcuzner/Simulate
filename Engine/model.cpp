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

const std::string &Model::getName() const
{
    return this->name;
}

void Model::setName(const std::string &name)
{
    this->name = name;

    this->sigNameChanged(this, name);
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
    this->entriesById[entry->getId()] = entry;

    this->addBlock(entry);
    this->sigEntryAdded(this, entry);

    return entry;
}

bool Model::removeEntry(const std::string &name)
{
    if (this->entries.count(name))
    {
        boost::shared_ptr<IEntryBlock> entry = this->entries[name];
        this->removeBlock(entry);

        return true;
    }

    return false;
}

const std::map<std::string, boost::shared_ptr<IEntryBlock> > &Model::getEntries() const
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
    this->exitsById[exit->getId()] = exit;

    this->addBlock(exit);
    this->sigExitAdded(this, exit);

    return exit;
}

bool Model::removeExit(const std::string &name)
{
    if (this->exits.count(name))
    {
        boost::shared_ptr<IExitBlock> exit = this->exits[name];
        this->removeBlock(exit);

        return true;
    }

    return false;
}

const std::map<std::string, boost::shared_ptr<IExitBlock> > &Model::getExits() const
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

    this->addBlock(block);

    return block;
}

bool Model::removeBlock(boost::shared_ptr<IBlock> block)
{
    if (this->blocks.count(block->getId()))
    {
        if (this->entriesById.count(block->getId()))
        {
            //this is an entry
            boost::shared_ptr<IEntryBlock> entry = this->entriesById.at(block->getId());
            this->entriesById.erase(entry->getId());
            this->entries.erase(entry->getEntryName());

            this->sigEntryRemoved(this, entry);
        }
        if (this->exitsById.count(block->getId()))
        {
            //this is an exit
            boost::shared_ptr<IExitBlock> exit = this->exitsById.at(block->getId());
            this->exitsById.erase(exit->getId());
            this->exits.erase(exit->getExitName());

            this->sigExitRemoved(this, exit);
        }
        if (this->modelBlocks.count(block->getId()))
        {
            //this is a modelblock
            this->modelBlocks.erase(block->getId());
        }

        this->blocks.erase(block->getId());
        this->sigBlockRemoved(this, block);

        return true;
    }

    return false;
}

bool Model::removeBlock(int id)
{
    if (this->blocks.count(id))
        return this->removeBlock(this->blocks.at(id));

    return false;
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

    if (modelBlock)
    {
        this->addBlock(modelBlock);
        this->modelBlocks[modelBlock->getId()] = modelBlock;
    }

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

void Model::addBlock(boost::shared_ptr<IBlock> block)
{
    if (block)
    {
        this->blocks[block->getId()] = block;

        block->sigBlockChanged.connect(boost::bind(&Model::onBlockChanged, this, _1));
        block->sigConnected.connect(boost::bind(&Model::onBlockConnected, this, _1, _2, _3, _4));
        block->sigDataChanged.connect(boost::bind(&Model::onBlockDatachanged, this, _1, _2));
        block->sigInputAdded.connect(boost::bind(&Model::onBlockInputAdded, this, _1, _2));
        block->sigInputRemoved.connect(boost::bind(&Model::onBlockInputRemoved, this, _1, _2));
        block->sigOutputAdded.connect(boost::bind(&Model::onBlockOutputAdded, this, _1, _2));
        block->sigOutputRemoved.connect(boost::bind(&Model::onBlockOutputRemoved, this, _1, _2));

        this->sigBlockAdded(this, block);
    }
}

void Model::onBlockChanged(IBlock *block)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockChanged(this, blockPtr);

}

void Model::onBlockConnected(IBlock *block, const std::string &output, boost::shared_ptr<IBlock> toBlock, const std::string &input)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockConnected(this, blockPtr, output, toBlock, input);
}

void Model::onBlockOptionChanged(IBlock *block, const std::string &name)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockOptionChanged(this, blockPtr, name);
}

void Model::onBlockDatachanged(IBlock *block, const std::string &name)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockDataChanged(this, blockPtr, name);
}

void Model::onBlockInputAdded(IBlock *block, boost::shared_ptr<IBlockInput> input)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockInputAdded(this, blockPtr, input);
}

void Model::onBlockInputRemoved(IBlock *block, boost::shared_ptr<IBlockInput> input)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockInputRemoved(this, blockPtr, input);
}

void Model::onBlockOutputAdded(IBlock *block, boost::shared_ptr<IBlockOutput> output)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockOutputAdded(this, blockPtr, output);
}

void Model::onBlockOutputRemoved(IBlock *block, boost::shared_ptr<IBlockOutput> output)
{
    boost::shared_ptr<IBlock> blockPtr = this->blocks[block->getId()];

    this->sigBlockOutputRemoved(this, blockPtr, output);
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
