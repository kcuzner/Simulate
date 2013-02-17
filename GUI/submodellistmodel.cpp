#include "submodellistmodel.h"

SubmodelListModel::SubmodelListModel(boost::shared_ptr<ISimulation> simulation, QObject *parent) :
    QAbstractListModel(parent)
{
    if (simulation)
    {
        boost::shared_ptr<IModel> rootModel = simulation->getRootModel();
        typedef std::pair<std::string, boost::shared_ptr<IModel> > ModelRecord;
        foreach(ModelRecord record, simulation->getModels())
        {
            //we record everything but the root model in this list
            if (record.second != rootModel)
            {
                this->listItems.append(new ListItem(record.second));
            }
        }
    }
}

int SubmodelListModel::columnCount(const QModelIndex &parent) const
{
    return 1; //1 column only
}

int SubmodelListModel::rowCount(const QModelIndex &parent) const
{
    return this->listItems.length();
}

QVariant SubmodelListModel::data(const QModelIndex &index, int role) const
{
    //index must be valid
    if (!index.isValid())
        return QVariant();

    //index must be inside our list
    if (index.row() > listItems.size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return listItems.at(index.row())->data(index.column());
    }
    else
    {
        return QVariant();
    }
}


SubmodelListModel::ListItem::ListItem(boost::shared_ptr<IModel> model)
{
    this->model = model;
}

QVariant SubmodelListModel::ListItem::data(int column)
{
    if (column == 0)
        return QString::fromStdString(model->getName());
    else
        return QVariant();
}
