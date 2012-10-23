#ifndef PLUGINTRACKER_H
#define PLUGINTRACKER_H

#define PLUGIN_DEFAULT_DIRECTORY "plugins/"

#ifdef Q_WS_WIN
#define PLUGIN_NAME_FILTERS "*.dll"
#else
#define PLUGIN_NAME_FILTERS "*.so"
#endif

#include "ipluginbase.h"
#include "simulation/iblockplugin.h"
#include "simulation/iblockfactory.h"

#include <QObject>
#include <QString>
#include <QDir>
#include <QHash>
#include <QAbstractItemModel>
#include <QVariant>
#include <QSharedPointer>
#include <QQueue>

class PluginTracker : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PluginTracker(Simulation::IBlockFactory* blockFactory, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool hasErrors();
    QString getError();
    
signals:
    void pluginLoaded(QSharedPointer<IPluginBase> plugin);
    void errorsWhileLoading();

public slots:
    void scan();
    void selectDirectory(QString directory);
    
protected:
    class PluginTrackerNode
    {
    public:
        PluginTrackerNode(bool plugin, QString name, QString description, PluginTrackerNode* parent = 0);
        ~PluginTrackerNode();

        void appendChild(PluginTrackerNode* child);

        PluginTrackerNode* child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        int row() const;
        PluginTrackerNode* parent();

    private:
        PluginTrackerNode* parentNode;
        QList<PluginTrackerNode*> children;
        QString name, description;

    };

    QDir pluginDirectory;
    QHash<QString, IPluginBase* > plugins;
    QHash<QString, Simulation::IBlockPlugin*> blockPlugins;
    QQueue<QString> errors;
    PluginTrackerNode* root;

    Simulation::IBlockFactory* blockFactory;
};

#endif // PLUGINTRACKER_H
