#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <QString>
#include <QHash>

#include "block.h"

class BlockFactory
{
public:

    /**
     * @brief Returns the singleton instance of this block
     * @return
     */
    static BlockFactory* getInstance();

    void declareBlock(QString name, Simulation::Block* (*generate)());

private:
    BlockFactory();

    static BlockFactory* mInstance;
    QHash<QString, Simulation::Block* (*)()> blocks;
};

BlockFactory* BlockFactory::mInstance;

#endif // BLOCKFACTORY_H
