#include "blockfactorygrouplistmodel.h"

BlockFactoryGroupListModel::BlockFactoryGroupListModel(boost::shared_ptr<ISimulationCore> core, const std::string &groupName, QObject* parent = 0)
    : QAbstractListModel(parent)
{
    this->groupName = groupName;

    this->icon = QIcon("../data/pictures.png");

    //latch on to the block factory and follow it around
    core->getBlockFactory()->sigBlockAdded.connect(boost::bind(&BlockFactoryGroupListModel::onBlockAdded, this, _1, _2));

    //scan the blocks for this group
    if (core->getBlockFactory()->getValidBlockNames().count(groupName))
    {
        for(std::list<std::string>::const_iterator iter = core->getBlockFactory()->getValidBlockNames().at(groupName).begin(); iter != core->getBlockFactory()->getValidBlockNames().at(groupName).end(); iter++)
        {
            this->blockNames.push_back(QString((*iter).c_str()));
        }
    }
}

int BlockFactoryGroupListModel::rowCount(const QModelIndex &) const
{
    return this->blockNames.size();
}

QVariant BlockFactoryGroupListModel::data(const QModelIndex &index, int role) const
{
    if (index.column() != 0 || index.row() >= this->blockNames.size())
        return QVariant(); //nothing outside our bounds


    if (role == Qt::DisplayRole)
    {
        return QVariant(this->blockNames.at(index.row()));
    }
    else if (role == Qt::DecorationRole)
    {
        return QVariant(this->icon);
    }

    return QVariant();
}

void BlockFactoryGroupListModel::onBlockAdded(const std::string &group, const std::string &name)
{
    if (this->groupName == group)
    {
        this->blockNames.push_back(QString(name.c_str()));
        QModelIndex topLeft = this->createIndex(this->blockNames.size() - 1, 0);
        emit this->dataChanged(topLeft, topLeft);
    }
}
