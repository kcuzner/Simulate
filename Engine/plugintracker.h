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
#include <QAbstractListModel>
#include <QVariant>
#include <QSharedPointer>
#include <QQueue>

class PluginTracker : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PluginTracker(Simulation::IBlockFactory* blockFactory, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool hasErrors();
    QString getError();
    
signals:
    void pluginLoaded(QSharedPointer<IPluginBase> plugin);
    void errorsWhileLoading();

public slots:
    void scan();
    void selectDirectory(QString directory);
    
protected:
    QDir pluginDirectory;
    QHash<QString, IPluginBase* > plugins;
    QHash<QString, Simulation::IBlockPlugin*> blockPlugins;
    QQueue<QString> errors;

    Simulation::IBlockFactory* blockFactory;
};

#endif // PLUGINTRACKER_H
