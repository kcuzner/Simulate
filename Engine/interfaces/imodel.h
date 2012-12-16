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

//forward definition of IModelBlock (imodelblock.h)
class IModelBlock;

/**
 * @brief Interface to a model encapsulating a number of blocks
 */
class IModel
{
public:
    virtual ~IModel() { }

    /**
     * TODO: Add methods for tracking blocks like an id or something
     */

    virtual bool addEntry(const std::string& name) = 0;
    virtual bool removeEntry(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IEntryBlock> >& getEntries() = 0;

    virtual bool addExit(const std::string& name) = 0;
    virtual bool removeExit(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IExitBlock> >& getExits() = 0;

    /**
     * @brief Creates a block in this model with the passed group and name
     * @param group Group to use
     * @param name Name to use
     * @return The created block
     */
    virtual boost::shared_ptr<IBlock> createBlock(const std::string& group, const std::string& name) = 0;
    virtual bool removeBlock(boost::shared_ptr<IBlock> block) = 0;
    virtual bool removeBlock(int id) = 0;

    /**
     * @brief Adds a modelblock to this model
     * @param model Model to add
     * @return
     */
    virtual boost::shared_ptr<IModelBlock> addModel(boost::shared_ptr<IModel> model) = 0;

    /**
     * @brief Returns all the blocks this model has
     * @return Blocks sorted by id
     */
    virtual const std::map<int, boost::shared_ptr<IBlock> >& getBlocks() = 0;
    virtual boost::shared_ptr<IBlock> getBlock(int blockId) = 0;

    /**
     * TODO: Make loading interfaces and have the model take them in directly
     */

    boost::signals2::signal<void (boost::shared_ptr<IEntryBlock>)> sigEntryAdded;
    boost::signals2::signal<void (boost::shared_ptr<IEntryBlock>)> sigEntryRemoved;
    boost::signals2::signal<void (boost::shared_ptr<IExitBlock>)> sigExitAdded;
    boost::signals2::signal<void (boost::shared_ptr<IExitBlock>)> sigExitRemoved;
    boost::signals2::signal<void (boost::shared_ptr<IBlock>)> sigBlockAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlock>)> sigBlockRemoved;
};

#endif // IMODEL_H
