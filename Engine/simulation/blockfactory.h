#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <QString>
#include <QHash>

#include "model.h"
#include "../interfaces/iblockcore.h"
#include "../interfaces/iblockfactory.h"
#include <QAbstractItemModel>

namespace Simulation
{
    class Block;

    class BlockFactory : public QObject, public Interfaces::IBlockFactory
    {
        Q_OBJECT

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
         * @return unique id for this block
         */
        virtual int declareBlock(QString group, QString name, QIcon icon, Interfaces::GenerateBlock generator);

        /**
         * @brief Generates a block with the given name
         * @param name
         * @return
         */
        Block* generateBlock(int id, Model *model);

        Block* generateBlock(QString group, QString name, Model* model);

        QStringList getGroups();

        class BlockInfo
        {
        public:
            BlockInfo(int id, QString group, QString name, QIcon icon, Interfaces::GenerateBlock generator);

            int getId();
            QString getName();
            QIcon getIcon();
            Block* generate(Model* model);
        private:
            int id;
            QString group, name;
            QIcon icon;
            Interfaces::GenerateBlock generator;
        };

        QHash<QString, QSharedPointer<BlockFactory::BlockInfo> > getBlocks(QString groupName);

    signals:
        void blockAdded(QSharedPointer<BlockFactory::BlockInfo>);

    private:
        BlockFactory();

        static BlockFactory* instance;
        int currentBlockId;
        QHash<int, QSharedPointer<BlockInfo> > blocksById; //sorted by id
        QHash<QString, QHash<QString, QSharedPointer<BlockInfo> > > blocks; //sorted by group
    };

}

#endif // BLOCKFACTORY_H
