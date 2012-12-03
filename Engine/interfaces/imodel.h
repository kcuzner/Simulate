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

/**
 * @brief Interface to a model encapsulating a number of blocks
 */
class IModel
{
public:
    virtual ~IModel() { }

    virtual int getNextId() = 0;

    virtual bool addEntry(const std::string& name) = 0;
    virtual bool removeEntry(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IEntryBlock> >& getEntries() = 0;

    virtual bool addExit(const std::string& name) = 0;
    virtual bool removeExit(const std::string& name) = 0;
    virtual const std::map<std::string, boost::shared_ptr<IExitBlock> >& getExits() = 0;

    virtual bool addBlock(boost::shared_ptr<IBlock> block) = 0;
    virtual bool removeBlock(boost::shared_ptr<IBlock> block) = 0;
    virtual bool hasBlock(boost::shared_ptr<IBlock> block) = 0;
    virtual bool hasBlock(int id) = 0;

    virtual const std::map<int, boost::shared_ptr<IBlock> >& getBlocks();

    boost::signals2::signal<void (boost::shared_ptr<IEntryBlock>)> sigEntryAdded;
    boost::signals2::signal<void (boost::shared_ptr<IEntryBlock>)> sigEntryRemoved;
    boost::signals2::signal<void (boost::shared_ptr<IExitBlock>)> sigExitAdded;
    boost::signals2::signal<void (boost::shared_ptr<IExitBlock>)> sigExitRemoved;
    boost::signals2::signal<void (boost::shared_ptr<IBlock>)> sigBlockAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlock>)> sigBlockRemoved;
};

#endif // IMODEL_H
