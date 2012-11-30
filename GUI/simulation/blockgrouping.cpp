#include "blockgrouping.h"

using namespace Simulation;

BlockGrouping::BlockGrouping()
{
}


QModelIndex Simulation::BlockGrouping::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex Simulation::BlockGrouping::parent(const QModelIndex &child) const
{
}

int Simulation::BlockGrouping::rowCount(const QModelIndex &parent) const
{
}

int Simulation::BlockGrouping::columnCount(const QModelIndex &parent) const
{
}

QVariant Simulation::BlockGrouping::data(const QModelIndex &index, int role) const
{
}


BlockGrouping::BlockEntry::BlockEntry(QString &name, QIcon icon, QUuid blockUuid)
{
    this->name = name;
    this->icon = icon;
    this->uuid = blockUuid;
}

QString BlockGrouping::BlockEntry::getName()
{
    return name;
}

QIcon BlockGrouping::BlockEntry::getIcon()
{
    return icon;
}

QUuid BlockGrouping::BlockEntry::getUUID()
{
    return uuid;
}
