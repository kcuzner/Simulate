#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>
#include <QHash>

namespace Simulation
{
    class Block;
    class EntryBlock;
    class ExitBlock;

    class Model : public QObject
    {
        Q_OBJECT
    public:
        explicit Model(QObject *parent = 0);

        QList<Block*> getBlocks();

        Block* addBlock(Block* block);
        EntryBlock *addEntry(QString &name);
        ExitBlock *addExit(QString name);

    signals:
        void blockAdded(Block* block);
        void blockRemoved(Block* block);
        void entryAdded(EntryBlock* block);
        void exitAdded(ExitBlock* block);
        void entryRemoved(EntryBlock* block);
        void exitRemoved(ExitBlock* block);

    public slots:
        void removeEntry(QString name);
        void removeEntry(EntryBlock* block);
        void removeExit(QString name);
        void removeExit(ExitBlock* block);

    protected:
        QList<Block*> blocks;
        QHash<QString, EntryBlock*> entries;
        QHash<QString, ExitBlock*> exits;

    };

}

#endif // MODEL_H
