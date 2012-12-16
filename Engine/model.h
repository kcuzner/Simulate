#ifndef MODEL_H
#define MODEL_H

#include "interfaces/imodel.h"
#include "interfaces/iblockfactory.h"

/**
 * @brief The Model class, using the default block factory
 */
class Model : IModel
{
public:
    Model(boost::shared_ptr<IBlockFactory> factory);

    virtual bool addEntry(const std::string& name);
    virtual bool removeEntry(const std::string& name);
    virtual const std::map<std::string, boost::shared_ptr<IEntryBlock> >& getEntries();

    virtual bool addExit(const std::string& name);
    virtual bool removeExit(const std::string& name);
    virtual const std::map<std::string, boost::shared_ptr<IExitBlock> >& getExits();

    virtual boost::shared_ptr<IBlock> createBlock(const std::string& group, const std::string& name);
    virtual bool removeBlock(boost::shared_ptr<IBlock> block);
    virtual bool removeBlock(int id);

    virtual boost::shared_ptr<IModelBlock> addModel(boost::shared_ptr<IModel> model);

    virtual const std::map<int, boost::shared_ptr<IBlock> >& getBlocks();
    virtual boost::shared_ptr<IBlock> getBlock(int blockId);

protected:
    long currentId;
    std::map<int, boost::shared_ptr<IBlock> > blocks;
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries;
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits;

    long getNextId();

    boost::shared_ptr<IBlockFactory> factory;
};

#endif // MODEL_H
