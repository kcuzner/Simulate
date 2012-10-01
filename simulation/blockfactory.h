#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <QString>
#include <QHash>

namespace Simulation
{
    class Block;

    typedef Block* (*GenerateBlock)();

    class BlockFactory
    {
    public:

        static BlockFactory* getInstance();

        void declareBlock(QString name, GenerateBlock generator);

        Block* generateBlock(QString name);

    protected:
        BlockFactory();

        static BlockFactory* instance;
        QHash<QString, GenerateBlock> blocks;
    };

}

#endif // BLOCKFACTORY_H
