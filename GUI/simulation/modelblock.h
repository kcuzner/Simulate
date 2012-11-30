#ifndef MODELBLOCK_H
#define MODELBLOCK_H

#include "block.h"
#include "entryblock.h"
#include "exitblock.h"

#include <QSharedPointer>

namespace Simulation
{
    /**
     * @brief Block which holds and executes a block in a child context
     */
    class ModelBlock : Block
    {
    public:
        ModelBlock(Model* model, QSharedPointer<Model> executionModel);

        virtual QStringList getOptionsList();
        virtual void execute(Context *context);

    protected slots:
        void modelEntryAdded(QSharedPointer<EntryBlock> entry);
        void modelExitAdded(QSharedPointer<ExitBlock> exit);
        void modelEntryRemoved(QSharedPointer<EntryBlock> entry);
        void modelExitRemoved(QSharedPointer<ExitBlock> exit);

    protected:
        QSharedPointer<Model> model;
    };

}

#endif // MODELBLOCK_H
