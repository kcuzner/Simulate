#ifndef BLOCKGROUPING_H
#define BLOCKGROUPING_H

#include <QAbstractItemModel>
#include <QIcon>

#include "../interfaces/iblockfactory.h"

namespace Simulation
{

    class BlockGrouping : public QAbstractItemModel
    {
    public:
        BlockGrouping();

        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;

    protected:
        class BlockEntry
        {
        public:
            BlockEntry(QString& name, QIcon icon, QUuid blockUuid);

            QString getName();
            QIcon getIcon();
            QUuid getUUID();
        private:
            QString name;
            QIcon icon;
            QUuid uuid;
        };
    };

}

#endif // BLOCKGROUPING_H
