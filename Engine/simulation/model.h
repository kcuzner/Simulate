#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>

namespace Simulation
{
    class Block;

    class Model : public QObject
    {
        Q_OBJECT
    public:
        explicit Model(QObject *parent = 0);

        QList<Block*> getBlocks();

    signals:
        void blockAdded(Block* block);

    public slots:
        void addBlock(Block* block);

    protected:
        QList<Block*> blocks;

    };

}

#endif // MODEL_H
