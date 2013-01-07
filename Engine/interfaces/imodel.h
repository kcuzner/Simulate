#ifndef IMODEL_H
#define IMODEL_H

#include <string>
#include <map>
#include <vector>

#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "iblock.h"
#include "ientryblock.h"
#include "iexitblock.h"

#include "ifilemodeldescription.h"

//forward definition of IModelBlock (imodelblock.h)
class IModelBlock;

//forward definition of IBlockFactory (iblockfactory.h)
class IBlockFactory;

/**
 * @brief Interface to a model encapsulating a number of blocks
 */
class IModel
{
public:
    virtual ~IModel() { }

    /**
     * @brief Each model can be given a name. It is the responsibility of the
     * program to ensure that model names are unique throughout the engine.
     * @return
     */
    virtual const std::string& getName() const = 0;
    virtual void setName(const std::string& name) = 0;

    virtual boost::shared_ptr<IEntryBlock> addEntry(const std::string& name) = 0;
    virtual boost::shared_ptr<IEntryBlock> addEntry(int id, const std::string& name) = 0;
    virtual bool removeEntry(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IEntryBlock> >& getEntries() const = 0;

    virtual boost::shared_ptr<IExitBlock> addExit(const std::string& name) = 0;
    virtual boost::shared_ptr<IExitBlock> addExit(int id, const std::string& name) = 0;
    virtual bool removeExit(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IExitBlock> >& getExits() const = 0;

    /**
     * @brief Creates a block in this model with the passed group and name
     * @param group Group to use
     * @param name Name to use
     * @return The created block
     */
    virtual boost::shared_ptr<IBlock> createBlock(const std::string& group, const std::string& name) = 0;
    virtual boost::shared_ptr<IBlock> createBlock(int id, const std::string& group, const std::string& name) = 0;

    /**
     * @brief Removes a block (use this for entries, exits, modelblocks, and normal blocks)
     * @param block
     * @return
     */
    virtual bool removeBlock(boost::shared_ptr<IBlock> block) = 0;
    virtual bool removeBlock(int id) = 0;

    /**
     * @brief Adds a modelblock to this model. This should check for infinite recursion
     * @param model Model to add
     * @return
     */
    virtual boost::shared_ptr<IModelBlock> addModel(boost::shared_ptr<IModel> model) = 0;
    virtual boost::shared_ptr<IModelBlock> addModel(int id, boost::shared_ptr<IModel> model) = 0;
    virtual const std::map<int, boost::shared_ptr<IModelBlock> >& getModelBlocks() = 0;

    /**
     * @brief Returns all the blocks this model has. This should include entries, exits,
     * and modelblocks.
     * @return Blocks sorted by id
     */
    virtual const std::map<int, boost::shared_ptr<IBlock> >& getBlocks() = 0;
    virtual boost::shared_ptr<IBlock> getBlock(int blockId) = 0;

    //bubbled events
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>)> sigBlockChanged;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, const std::string&, boost::shared_ptr<IBlock>, const std::string&)> sigBlockConnected;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, const std::string&)> sigBlockOptionChanged;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, const std::string&)> sigBlockDataChanged;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockInput>)> sigBlockInputAdded;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockInput>)> sigBlockInputRemoved;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockOutput>)> sigBlockOutputAdded;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockOutput>)> sigBlockOutputRemoved;

    //model events
    boost::signals2::signal<void (IModel*)> sigModelChanged;
    boost::signals2::signal<void (IModel*, const std::string&)> sigNameChanged;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IEntryBlock>)> sigEntryAdded;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IEntryBlock>)> sigEntryRemoved;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IExitBlock>)> sigExitAdded;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IExitBlock>)> sigExitRemoved;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>)> sigBlockAdded;
    boost::signals2::signal<void (IModel*, boost::shared_ptr<IBlock>)> sigBlockRemoved;
};

class IModelGenerator
{
public:
    virtual ~IModelGenerator() {}

    virtual const std::string& getModelTypeName() = 0;

    virtual boost::shared_ptr<IModel> generate(const std::string& name, boost::shared_ptr<IBlockFactory> factory) = 0;
};

#endif // IMODEL_H
