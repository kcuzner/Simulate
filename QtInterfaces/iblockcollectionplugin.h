#ifndef IBLOCKCOLLECTIONPLUGIN_H
#define IBLOCKCOLLECTIONPLUGIN_H

#include <QtPlugin>

#include <QList>

#include "iplugin.h"
#include "../Engine/interfaces/iblockcollection.h"

class IBlockCollectionPlugin : public IPlugin
{
public:
	virtual ~IBlockCollectionPlugin() { }

	virtual QList<boost::shared_ptr<IBlockCollection> > getBlockCollections() = 0;
};

Q_DECLARE_INTERFACE(IBlockCollectionPlugin, "comp.Simulate.Plugins.Engine.BlockCollection/1.0")

#endif
