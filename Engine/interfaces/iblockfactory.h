#ifndef IBLOCKFACTORY_H
#define IBLOCKFACTORY_H

#include <string>
#include <map>
#include <list>


#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "iblock.h"
#include "imodelblock.h"
#include "imodel.h"

/**
 * @brief Interface to a block factory
 *
 *
 */
class IBlockFactory
{
public:
    virtual ~IBlockFactory() {}

    /**
     * @brief Returns a map sorted by group and name with the valid block names for this factory
     * @return
     */
    virtual const std::map<std::string, std::list<std::string> >& getValidBlockNames() const = 0;

    /**
     * @brief Generates a block
     * @param id Id to use (this should be project unique)
     * @param group Group the block can be found in
     * @param name Name of the block to construct
     * @return pointer to new block or null if no block under the group/name was found
     */
    virtual boost::shared_ptr<IBlock> generateBlock(int id, const std::string& group, const std::string& name) = 0;
    /**
     * @brief Generates a block that uses the passed model as its computation
     * @param id Id to use (this should be project unique)
     * @return pointer to new block or null if unsupported or model pointer was invalid
     */
    virtual boost::shared_ptr<IModelBlock> generateModelBlock(int id, boost::weak_ptr<IModel> model) = 0;

    /**
     * @brief Adds a generator function for the named block to this factory
     * @param generator Function that can generate this block
     * @param group Group to put the block under
     * @param name Name of the block
     */
    virtual void declareBlock(const boost::function<boost::shared_ptr<IBlock> (int id)>& generator, const std::string& group, const std::string& name) = 0;


    boost::signals2::signal<void (const std::string& group, const std::string& name)> sigBlockAdded;

};

#endif // IBLOCKFACTORY_H
