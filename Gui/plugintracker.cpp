#include "plugintracker.h"

#include "ipluginbase.h"

#include <QPluginLoader>
#include <iostream>
using namespace std;

PluginTracker::PluginTracker(QObject *parent) :
    QAbstractListModel(parent)
{
    this->pluginDirectory = QDir::current();
    this->pluginDirectory.cd(PLUGIN_DEFAULT_DIRECTORY);

    this->rescan();
}

QVariant PluginTracker::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return this->plugins.values().at(index.row())->getName();
    }

    return QVariant();
}

int PluginTracker::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return this->plugins.count();
}

void PluginTracker::rescan()
{
    QStringList filters;
    filters << PLUGIN_NAME_FILTERS;
    this->pluginDirectory.setNameFilters(filters);

    QStringList files = this->pluginDirectory.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QString file;

    cout << "Scanning" << this->pluginDirectory.absolutePath().toLocal8Bit().data() << endl;

    foreach(file, files)
    {
        if (this->plugins.keys().contains(file))
            continue; //skip to the next one

        QPluginLoader loader(this->pluginDirectory.absoluteFilePath(file));
        QObject* instance = loader.instance();
        if (!instance) {
            cout << loader.errorString().toLocal8Bit().data() << endl;
        }
        //attempt to cast the instance to one of our plugins
        IPluginBase* plugin = qobject_cast<IPluginBase*>(instance);
        if (plugin) {
            cout << file.toLocal8Bit().data() << endl;
            cout.flush();
        }
    }
}

void PluginTracker::selectDirectory(QString directory)
{
    this->pluginDirectory = QDir(directory);
}



