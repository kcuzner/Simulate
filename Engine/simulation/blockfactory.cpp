#include "blockfactory.h"
#include "block.h"

using namespace Simulation;
using namespace Interfaces;

BlockFactory* BlockFactory::instance;

BlockFactory *BlockFactory::getInstance()
{
    if (instance)
        return instance;

    instance = new BlockFactory();

    return instance;
}

int BlockFactory::declareBlock(QString group, QString name, QIcon icon, GenerateBlock generator)
{
    QSharedPointer<BlockInfo> info(new BlockInfo(this->currentBlockId, group, name, icon, generator));

    this->blocks[group][name] = info;
    this->blocksById[info->getId()] = info;

    emit blockAdded(info);

    return info->getId();
}

Block *BlockFactory::generateBlock(int id, Model* model)
{
    return this->blocksById[id]->generate(model);
}

Block *BlockFactory::generateBlock(QString group, QString name, Model *model)
{
    return this->blocks[group][name]->generate(model);
}

QStringList BlockFactory::getGroups()
{
    return this->blocks.keys();
}

QHash<QString, QSharedPointer<BlockFactory::BlockInfo> > BlockFactory::getBlocks(QString groupName)
{
    return this->blocks[groupName];
}

BlockFactory::BlockFactory()
{
    this->currentBlockId = 0;
}


BlockFactory::BlockInfo::BlockInfo(int id, QString group, QString name, QIcon icon, GenerateBlock generator)
{
    this->id = id;
    this->group = group;
    this->name = name;
    this->icon = icon;
    this->generator = generator;
}

int BlockFactory::BlockInfo::getId()
{
    return this->id;
}

QString BlockFactory::BlockInfo::getName()
{
    return this->name;
}

QIcon BlockFactory::BlockInfo::getIcon()
{
    return this->icon;
}

Block *BlockFactory::BlockInfo::generate(Model *model)
{
    return new Block(model, QSharedPointer<IBlockCore>(this->generator(model)));
}
