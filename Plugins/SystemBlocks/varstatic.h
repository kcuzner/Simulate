#ifndef VARSTATIC_H
#define VARSTATIC_H

#include "../../Engine/simulation/block.h"
#include "../../Engine/simulation/context.h"

namespace Blocks
{

    class VarStatic : Simulation::Block
    {
        Q_OBJECT

    public:
        VarStatic(Simulation::Model *model);
        ~VarStatic();

        static Block* generate(Simulation::Model *model);

        virtual void compute(Simulation::StepContext* context);

        virtual QStringList getOptionsList();

    public slots:
    };

}

#endif // VARSTATIC_H
