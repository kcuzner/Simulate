#ifndef IENGINEPLUGIN_H
#define IENGINEPLUGIN_H

#include <QtPlugin>

#include <QHash>

#include "iplugin.h"
#include "../Engine/interfaces/iengine.h"

/**
 * @brief Qt Plugin interface for a plugin containing one or more engines
 */
class IEnginePlugin : public IPlugin
{
public:
    virtual ~IEnginePlugin() {}

    /**
     * @brief Returns the engine generator functions along with the engine names for this plugin
     * @return
     */
    virtual QHash<std::string, boost::function<boost::shared_ptr<IEngine> (boost::shared_ptr<IModel>, int, double)> > getEngines() = 0;
};

Q_DECLARE_INTERFACE(IEnginePlugin, "comp.Simulate.Plugins.Engine/1.0")

#endif // IENGINEPLUGIN_H
