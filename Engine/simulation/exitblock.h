#ifndef EXITBLOCK_H
#define EXITBLOCK_H

#include "block.h"

namespace Simulation
{

    class ExitBlock : public Block
    {
        Q_OBJECT

    public:
        ExitBlock(Model* model, QString name);

        virtual QStringList getOptionsList();
        virtual void compute(StepContext *context);

        QString getName();

    protected:
        QString name;
    };

}

#endif // EXITBLOCK_H
