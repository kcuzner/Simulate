#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSharedPointer>

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

        QList<QSharedPointer<Block> > getBlocks();

        void addBlock(QSharedPointer<Block> block);
        QSharedPointer<EntryBlock> addEntry(const QString &name);
        QSharedPointer<ExitBlock> addExit(const QString &name);

    signals:
        void blockAdded(QSharedPointer<Block> block);
        void blockRemoved(QSharedPointer<Block> block);
        void entryAdded(QSharedPointer<EntryBlock> block);
        void exitAdded(QSharedPointer<ExitBlock> block);
        void entryRemoved(QSharedPointer<EntryBlock> block);
        void exitRemoved(QSharedPointer<ExitBlock> block);

    public slots:
        void removeEntry(const QString &name);
        void removeExit(const QString &name);

    protected:
        QList<QSharedPointer<Block> > blocks;
        QHash<QString,QSharedPointer<EntryBlock> > entries;
        QHash<QString, QSharedPointer<ExitBlock> > exits;

    };

}

#endif // MODEL_H
