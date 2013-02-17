#ifndef SIMULATIONTREEITEMMODEL_H
#define SIMULATIONTREEITEMMODEL_H

#include <QAbstractItemModel>
#include <QList>

#include "interfaces/isimulation.h"

class SimulationTreeItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SimulationTreeItemModel(boost::shared_ptr<ISimulation> simulation, QObject *parent = 0);
    ~SimulationTreeItemModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    
signals:
    
public slots:

protected:
    /**
     * @brief Base TreeItem class
     */
    class TreeItem
    {
    public:
        virtual ~TreeItem();

        virtual TreeItem* child(int row);
        virtual int childCount() const;
        virtual int columnCount() const = 0;
        virtual QVariant data(int column) const = 0;
        virtual int indexOf(TreeItem* item) const;
        virtual int row() const;
        virtual TreeItem* parent();

    protected:
        TreeItem(TreeItem* parent);

        void appendChild(TreeItem* child);

    private:
        TreeItem* mParent;
        QList<TreeItem*> mChildren;
    };

    /**
     * @brief Tree item for simulation objects
     */
    class SimulationTreeItem : public TreeItem
    {
    public:
        SimulationTreeItem(boost::shared_ptr<ISimulation> simulation, TreeItem* parent);

        virtual int columnCount() const;
        virtual QVariant data(int column) const;
    private:
        boost::shared_ptr<ISimulation> simulation;
    };

    /**
     * @brief Tree item for model objects
     */
    class ModelTreeItem : public TreeItem
    {
    public:
        ModelTreeItem(boost::shared_ptr<IModel> model, TreeItem* parent);

        virtual int columnCount() const;
        virtual QVariant data(int column) const;
    private:
        boost::shared_ptr<IModel> model;
    };
    
private:
    TreeItem* rootItem;
};

#endif // SIMULATIONTREEITEMMODEL_H
