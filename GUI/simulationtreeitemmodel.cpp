#include "simulationtreeitemmodel.h"

SimulationTreeItemModel::SimulationTreeItemModel(boost::shared_ptr<ISimulation> simulation, QObject *parent) :
    QAbstractItemModel(parent)
{
    this->rootItem = new SimulationTreeItem(simulation, NULL);
}

SimulationTreeItemModel::~SimulationTreeItemModel()
{
    delete this->rootItem;
}

QVariant SimulationTreeItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags SimulationTreeItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SimulationTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex SimulationTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex SimulationTreeItemModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int SimulationTreeItemModel::rowCount(const QModelIndex &parent) const
{
    TreeItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int SimulationTreeItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

int SimulationTreeItemModel::TreeItem::row() const
{
    if (this->mParent)
        return this->mParent->indexOf(const_cast<TreeItem*>(this));

    return 0;
}


SimulationTreeItemModel::TreeItem::~TreeItem()
{
    foreach(TreeItem* item, this->mChildren)
    {
        delete item;
    }
    this->mChildren.clear();
}

SimulationTreeItemModel::TreeItem *SimulationTreeItemModel::TreeItem::child(int row)
{
    return this->mChildren.value(row);
}

int SimulationTreeItemModel::TreeItem::childCount() const
{
    return this->mChildren.length();
}

int SimulationTreeItemModel::TreeItem::indexOf(SimulationTreeItemModel::TreeItem *item) const
{
    return this->mChildren.indexOf(item);
}

SimulationTreeItemModel::TreeItem *SimulationTreeItemModel::TreeItem::parent()
{
    return this->mParent;
}

SimulationTreeItemModel::TreeItem::TreeItem(SimulationTreeItemModel::TreeItem *parent)
{
    this->mParent = parent;
}

void SimulationTreeItemModel::TreeItem::appendChild(SimulationTreeItemModel::TreeItem *child)
{
    this->mChildren.append(child);
}


SimulationTreeItemModel::SimulationTreeItem::SimulationTreeItem(boost::shared_ptr<ISimulation> simulation, SimulationTreeItemModel::TreeItem *parent)
    : TreeItem(parent)
{
    this->simulation = simulation;

    //for each model, we create a child
    boost::shared_ptr<IModel> root = simulation->getRootModel();
    if (root)
    {
        //this is our child.
        this->appendChild(new ModelTreeItem(root, this));
    }
}

int SimulationTreeItemModel::SimulationTreeItem::columnCount() const
{
    return 1; //we have just one column which is the header
}

QVariant SimulationTreeItemModel::SimulationTreeItem::data(int column) const
{
    //header data comes from us since we are the root treeitem
    if (column == 0)
        return "Model Name";
    else
        return QVariant();
}


SimulationTreeItemModel::ModelTreeItem::ModelTreeItem(boost::shared_ptr<IModel> model, SimulationTreeItemModel::TreeItem *parent)
    : TreeItem(parent)
{
    this->model = model;

    //for each modelblock we create a child model tree item
    typedef std::pair<int, boost::shared_ptr<IModelBlock> > ModelBlockRecord;
    foreach(ModelBlockRecord record, model->getModelBlocks())
    {
        this->appendChild(new ModelTreeItem(record.second->getModel(), this));
    }
}

int SimulationTreeItemModel::ModelTreeItem::columnCount() const
{
    return 1; //we have just one column...the name
}

QVariant SimulationTreeItemModel::ModelTreeItem::data(int column) const
{
    if (column == 0)
    {
        return QString::fromStdString(model->getName());
    }
    else
    {
        return QVariant();
    }
}
