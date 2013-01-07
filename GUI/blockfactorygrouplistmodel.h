#ifndef BLOCKFACTORYGROUPLISTMODEL_H
#define BLOCKFACTORYGROUPLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QIcon>

#include "interfaces/isimulationcore.h"

class BlockFactoryGroupListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    BlockFactoryGroupListModel(boost::shared_ptr<ISimulationCore> core, const std::string& groupName, QObject *parent);

    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);

    void onBlockAdded(const std::string& group, const std::string& name);

protected:
    std::string groupName; //contains the name of the group this listens for

    QList<QString> blockNames; //contains the names of blocks added to this group
    QIcon icon;
};

#endif // BLOCKFACTORYGROUPLISTMODEL_H
