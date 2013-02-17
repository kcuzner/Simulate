#ifndef MODELLISTMODEL_H
#define MODELLISTMODEL_H

#include <QAbstractListModel>

#include "simulation.h"

class SubmodelListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SubmodelListModel(boost::shared_ptr<ISimulation> simulation, QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    
signals:
    
public slots:

protected:
    class ListItem
    {
    public:
        ListItem(boost::shared_ptr<IModel> model);

        QVariant data(int column);
    private:
        boost::shared_ptr<IModel> model;
    };

private:
    QList<ListItem*> listItems;
    
};

#endif // MODELLISTMODEL_H
