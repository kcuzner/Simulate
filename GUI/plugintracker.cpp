#include "plugintracker.h"

#include "interfaces/iblockplugin.h"

#include <QPluginLoader>
#include <iostream>
using namespace std;

using namespace Interfaces;

PluginTracker::PluginTracker(Interfaces::IBlockFactory* blockFactory, QObject *parent) :
    QAbstractItemModel(parent)
{
    this->pluginDirectory = QDir::current();
    this->pluginDirectory.cd(PLUGIN_DEFAULT_DIRECTORY);

    this->blockFactory = blockFactory;

    this->root = new PluginTrackerNode(false, "Plugins", "Loaded Plugins");
    //we support only blocks at the moment
    PluginTrackerNode* child = new PluginTrackerNode(false, "Block Plugins", "Block plugins to the simulation engine.", this->root);
    this->root->appendChild(child);
    PluginTrackerNode* plugin = new PluginTrackerNode(false, "System Blocks", "System blocks", child);
    child->appendChild(plugin);
}

QVariant PluginTracker::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    PluginTrackerNode* node = static_cast<PluginTrackerNode*>(index.internalPointer());

    return node->data(index.column());
}

int PluginTracker::rowCount(const QModelIndex &parent) const
{
    PluginTrackerNode* parentNode;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentNode = this->root;
    else
    {
        parentNode = static_cast<PluginTrackerNode*>(parent.internalPointer());
    }

    return parentNode->childCount();
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

QModelIndex PluginTracker::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    PluginTrackerNode* parentItem;

    if (!parent.isValid())
        parentItem = this->root;
    else
        parentItem = static_cast<PluginTrackerNode*>(parent.internalPointer());

    PluginTrackerNode* childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        cout << "oh noes! " << parentItem->data(0).toString().toLocal8Bit().data() << endl;
        return QModelIndex();
    }
    cout.flush();
}

QModelIndex PluginTracker::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    PluginTrackerNode* childNode = static_cast<PluginTrackerNode*>(child.internalPointer());
    PluginTrackerNode* parentNode = childNode->parent();

    if (parentNode == this->root)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
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
        Interfaces::IBlockPlugin* blockPlugin = qobject_cast<Interfaces::IBlockPlugin*>(instance);
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

/**
 * PluginTrackerNode methods
 */

PluginTracker::PluginTrackerNode::PluginTrackerNode(bool plugin, QString name, QString description, PluginTracker::PluginTrackerNode *parent)
{
    this->name = name;
    this->description = description;
    this->parentNode = parent;
}

PluginTracker::PluginTrackerNode::~PluginTrackerNode()
{
    qDeleteAll(this->children);
}

void PluginTracker::PluginTrackerNode::appendChild(PluginTracker::PluginTrackerNode *child)
{
    this->children.append(child);
}

PluginTracker::PluginTrackerNode *PluginTracker::PluginTrackerNode::child(int row)
{
    cout << this->name.toLocal8Bit().data() << " getting child at " << row << endl;
    cout.flush();
    return this->children.at(row);
}

int PluginTracker::PluginTrackerNode::childCount() const
{
    cout << this->name.toLocal8Bit().data() << " getting child count: " << this->children.count() << endl;
    cout.flush();
    return this->children.count();
}

int PluginTracker::PluginTrackerNode::columnCount() const
{
    return 2;
}

QVariant PluginTracker::PluginTrackerNode::data(int column) const
{
    if (column == 0)
    {
        return this->name;
    }
    else if (column == 1)
    {
        return this->description;
    }
    else
    {
        return QVariant();
    }
}

int PluginTracker::PluginTrackerNode::row() const
{
    if (this->parentNode)
    {
        return this->parentNode->children.indexOf(const_cast<PluginTrackerNode*>(this));
    }

    return 0;
}

PluginTracker::PluginTrackerNode *PluginTracker::PluginTrackerNode::parent()
{
    return this->parentNode;
}
