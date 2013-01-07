#ifndef MODEL_H
#define MODEL_H

#include "interfaces/imodel.h"
#include "interfaces/iblockfactory.h"

/**
 * @brief The Model class, using the default block factory
 */
class Model : public IModel
{
public:
    Model(const std::string& name, boost::shared_ptr<IBlockFactory> factory);

    virtual const std::string& getName() const;
    virtual void setName(const std::string &name);

    virtual boost::shared_ptr<IEntryBlock> addEntry(const std::string& name);
    virtual boost::shared_ptr<IEntryBlock> addEntry(int id, const std::string& name);
    virtual bool removeEntry(const std::string& name);
    virtual const std::map<std::string, boost::shared_ptr<IEntryBlock> >& getEntries() const;

    virtual boost::shared_ptr<IExitBlock> addExit(const std::string& name);
    virtual boost::shared_ptr<IExitBlock> addExit(int id, const std::string& name);
    virtual bool removeExit(const std::string& name);
    virtual const std::map<std::string, boost::shared_ptr<IExitBlock> >& getExits() const;

    virtual boost::shared_ptr<IBlock> createBlock(const std::string& group, const std::string& name);
    virtual boost::shared_ptr<IBlock> createBlock(int id, const std::string& group, const std::string& name);
    virtual bool removeBlock(boost::shared_ptr<IBlock> block);
    virtual bool removeBlock(int id);

    virtual boost::shared_ptr<IModelBlock> addModel(boost::shared_ptr<IModel> model);
    virtual boost::shared_ptr<IModelBlock> addModel(int id, boost::shared_ptr<IModel> model);
    virtual const std::map<int, boost::shared_ptr<IModelBlock> >& getModelBlocks();

    virtual const std::map<int, boost::shared_ptr<IBlock> >& getBlocks();
    virtual boost::shared_ptr<IBlock> getBlock(int blockId);

protected:
    long currentId;
    std::map<int, boost::shared_ptr<IBlock> > blocks;
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries;
    std::map<int, boost::shared_ptr<IEntryBlock> > entriesById;
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits;
    std::map<int, boost::shared_ptr<IExitBlock> > exitsById;
    std::map<int, boost::shared_ptr<IModelBlock> > modelBlocks;

    std::string name;

    long getNextId();
    bool useId(long id);

    /**
     * @brief Adds the block to the list in this model and attaches all the listeners.
     * This opposite of this is removeBlock.
     * @param block
     */
    void addBlock(boost::shared_ptr<IBlock> block);

    void onBlockChanged(IBlock* block);
    void onBlockConnected(IBlock* block, const std::string& output, boost::shared_ptr<IBlock> toBlock, const std::string& input);
    void onBlockOptionChanged(IBlock* block, const std::string& name);
    void onBlockDatachanged(IBlock* block, const std::string& name);
    void onBlockInputAdded(IBlock* block, boost::shared_ptr<IBlockInput> input);
    void onBlockInputRemoved(IBlock* block, boost::shared_ptr<IBlockInput> input);
    void onBlockOutputAdded(IBlock* block, boost::shared_ptr<IBlockOutput> output);
    void onBlockOutputRemoved(IBlock* block, boost::shared_ptr<IBlockOutput> output);

    boost::shared_ptr<IBlockFactory> factory;
};

class ModelGenerator : public IModelGenerator
{
public:
    ModelGenerator();

    virtual const std::string& getModelTypeName();

    virtual boost::shared_ptr<IModel> generate(const std::string &name, boost::shared_ptr<IBlockFactory> factory);

protected:
    std::string name;
};

#endif // MODEL_H
