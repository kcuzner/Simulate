#ifndef ENTRYBLOCK_H
#define ENTRYBLOCK_H

#include "block.h"

namespace Simulation
{
    class EntryBlock : public Block
    {
        Q_OBJECT

    public:
        EntryBlock(Model* model, QString name);

        virtual QStringList getOptionsList();
        virtual void execute(Context *context);

        QString getName();

    protected:
        QString name;
    };
}

#endif // ENTRYBLOCK_H
