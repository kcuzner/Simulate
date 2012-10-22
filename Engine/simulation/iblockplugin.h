#ifndef BLOCKPLUGIN_H
#define BLOCKPLUGIN_H

#include <QtPlugin>
#include <QObject>

#include "iblockfactory.h"
#include "../ipluginbase.h"

namespace Simulation
{

    /**
     * @brief Defines an interface for a plugin
     */
    class IBlockPlugin : IPluginBase
    {
        Q_INTERFACES(IPluginBase)
    public:
        virtual ~IBlockPlugin() {}

        /**
         * @brief Called when the plugin needs to declare its blocks to the passed factory
         * @param factory Factory to declare to
         */
        virtual void declareBlocks(IBlockFactory* factory) = 0;
    };

}

Q_DECLARE_INTERFACE(Simulation::IBlockPlugin, "org.Simulate.PluginInterfaces.BlockPlugin/1.0")

#endif // BLOCKPLUGIN_H
