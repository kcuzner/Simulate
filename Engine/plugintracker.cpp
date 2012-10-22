#include "plugintracker.h"

#include "simulation/iblockplugin.h"

#include <QPluginLoader>
#include <iostream>
using namespace std;

PluginTracker::PluginTracker(Simulation::IBlockFactory* blockFactory, QObject *parent) :
    QAbstractListModel(parent)
{
    this->pluginDirectory = QDir::current();
    this->pluginDirectory.cd(PLUGIN_DEFAULT_DIRECTORY);

    this->blockFactory = blockFactory;
    this->scan();
}

QVariant PluginTracker::data(const QModelIndex &index, int role) const
{
    cout << index.row() << endl;
    cout.flush();
    if (role == Qt::DisplayRole)
    {


        return this->plugins.values().at(index.row())->getName();
    }

    return QVariant();
}

QModelIndex PluginTracker::index(int row, int column, const QModelIndex &parent) const
{
}

int PluginTracker::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return this->plugins.count();
}

int PluginTracker::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return 2;
}

QVariant PluginTracker::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
        {
            return QVariant("Name");
        }
        else if (section == 1)
        {
            return QVariant("Description");
        }
    }

    return QVariant();
}

bool PluginTracker::hasErrors()
{
    return !this->errors.empty();
}

QString PluginTracker::getError()
{
    if (!this->errors.empty())
    {
        return this->errors.dequeue();
    }

    return QString();
}

void PluginTracker::scan()
{
    QStringList filters;
    filters << PLUGIN_NAME_FILTERS;
    this->pluginDirectory.setNameFilters(filters);

    QStringList files = this->pluginDirectory.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QString file;

    //cout << "Scanning" << this->pluginDirectory.absolutePath().toLocal8Bit().data() << endl;
    //cout.flush();

    bool errors = false;

    foreach(file, files)
    {
        if (this->plugins.keys().contains(file))
            continue; //skip to the next one

        QPluginLoader loader(this->pluginDirectory.absoluteFilePath(file));
        QObject* instance = loader.instance();
        if (!instance) {
            //there was an error
            QString error = "Error loading ";
            error.append(this->pluginDirectory.absoluteFilePath(file));
            error.append(" ");
            error.append(loader.errorString());
            this->errors.enqueue(error);
            errors = true;
        }
        //attempt to cast the instance to one of our plugins
        Simulation::IBlockPlugin* blockPlugin = qobject_cast<Simulation::IBlockPlugin*>(instance);
        if (blockPlugin) {
            this->plugins[blockPlugin->getName()] = blockPlugin;
            this->blockPlugins[blockPlugin->getName()] = blockPlugin;
            blockPlugin->declareBlocks(this->blockFactory);
        }
    }

    //errors = true;
    //this->errors.enqueue("Oh noes!!");
    //this->errors.enqueue("Oh noes again!");

    if (errors)
    {
        //emit our errors signal since some where queued
        //cout << "hi!" << endl;
        //cout.flush();
        if (!this->errors.empty())
            emit this->errorsWhileLoading();
    }
}

void PluginTracker::selectDirectory(QString directory)
{
    this->pluginDirectory = QDir(directory);
}
