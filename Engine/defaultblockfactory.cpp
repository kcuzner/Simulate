#include "defaultblockfactory.h"

#include "modelblock.h"

DefaultBlockFactory::DefaultBlockFactory()
{
}

boost::shared_ptr<DefaultBlockFactory> DefaultBlockFactory::instance;
boost::shared_ptr<DefaultBlockFactory> DefaultBlockFactory::getInstance()
{
    if (!instance)
        instance = boost::shared_ptr<DefaultBlockFactory>(new DefaultBlockFactory());

    return instance;
}

boost::shared_ptr<IBlock> DefaultBlockFactory::generateBlock(int id, const std::string &group, const std::string &name)
{
    if (this->generators.count(group) == 0)
    {
        //no group by that name
        return boost::shared_ptr<IBlock>();
    }

    if (this->generators.at(group).count(name) == 0)
    {
        //no block by that name in the group
        return boost::shared_ptr<IBlock>();
    }

    return this->generators.at(group).at(name)(id);
}

boost::shared_ptr<IModelBlock> DefaultBlockFactory::generateModelBlock(int id, boost::weak_ptr<IModel> model)
{
    if (model.expired())
        return boost::shared_ptr<IModelBlock>();

    return boost::shared_ptr<IModelBlock>(new ModelBlock(id, model.lock()));
}

void DefaultBlockFactory::declareBlock(const boost::function<boost::shared_ptr<IBlock> (int)> &generator, const std::string &group, const std::string &name)
{
    this->generators.at(group).at(name) = generator;
}
