#ifndef PLUGINTRACKER_H
#define PLUGINTRACKER_H

#define PLUGIN_DEFAULT_DIRECTORY "plugins/"

#ifdef Q_WS_WIN
#define PLUGIN_NAME_FILTERS "*.dll"
#else
#define PLUGIN_NAME_FILTERS "*.so"
#endif

#include "ipluginbase.h"

#include <QObject>
#include <QString>
#include <QDir>
#include <QHash>
#include <QAbstractListModel>
#include <QVariant>

class PluginTracker : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PluginTracker(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    
signals:
    void pluginLoaded(IPluginBase* plugin);

public slots:
    void rescan();
    void selectDirectory(QString directory);
    
protected:
    QDir pluginDirectory;
    QHash<QString, IPluginBase*> plugins;
};

#endif // PLUGINTRACKER_H
