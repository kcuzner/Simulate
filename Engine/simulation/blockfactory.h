#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <QString>
#include <QHash>

#include "model.h"
#include "../interfaces/iblockcore.h"
#include "../interfaces/iblockfactory.h"

namespace Simulation
{
    class Block;

    class BlockFactory : public Interfaces::IBlockFactory
    {
        Q_INTERFACES(Interfaces::IBlockFactory)

    public:

        /**
         * @brief Gets the singleton instance of the BlockFactory
         * @return
         */
        static BlockFactory* getInstance();

        /**
         * @brief Declares the existance of a block under a given name.
         * @param name
         * @param generator Static generator function from the block matching the GenerateBlock type
         */
        virtual void declareBlock(QString name, Interfaces::GenerateBlock generator);

        /**
         * @brief Generates a block with the given name
         * @param name
         * @return
         */
        Block* generateBlock(QString name, Model *model);

    //private:
        BlockFactory();

        static BlockFactory* instance;
        QHash<QString, Interfaces::GenerateBlock> blocks;
    };

}

#endif // BLOCKFACTORY_H
