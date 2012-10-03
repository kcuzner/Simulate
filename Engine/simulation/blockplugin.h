#ifndef BLOCKPLUGIN_H
#define BLOCKPLUGIN_H

#include <QtPlugin>
#include "blockfactory.h"

namespace Simulation
{

    /**
     * @brief Defines an interface for a plugin
     */
    class BlockPlugin
    {
    public:
        virtual ~BlockPlugin() {}

        /**
         * @brief Called when the plugin needs to declare its blocks to the passed factory
         * @param factory Factory to declare to
         */
        virtual void declareBlocks(BlockFactory* factory) = 0;
    };

}

Q_DECLARE_INTERFACE(Simulation::BlockPlugin, "org.Simulate.BlockPlugin")

#endif // BLOCKPLUGIN_H
