#ifndef DEFAULTBLOCKFACTORY_H
#define DEFAULTBLOCKFACTORY_H

#include "interfaces/iblockfactory.h"

#include <map>

class DefaultBlockFactory : public IBlockFactory
{
public:
    DefaultBlockFactory();

    virtual boost::shared_ptr<IBlock> generateBlock(int id, const std::string &group, const std::string &name);

    virtual boost::shared_ptr<IModelBlock> generateModelBlock(int id, boost::weak_ptr<IModel> model);

    virtual void declareBlock(const boost::function<boost::shared_ptr<IBlock> (int)> &generator, const std::string &group, const std::string &name);

protected:
    std::map<std::string, std::map<std::string, boost::function<boost::shared_ptr<IBlock> (int)> > > generators;
};

#endif // DEFAULTBLOCKFACTORY_H
