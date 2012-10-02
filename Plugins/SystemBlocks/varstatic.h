#ifndef VARSTATIC_H
#define VARSTATIC_H

#include "../simulation/block.h"
#include "../simulation/context.h"

namespace Blocks
{

    class VarStatic : Simulation::Block
    {
        Q_OBJECT

    public:
        VarStatic(Simulation::Model *model);
        ~VarStatic();

        static Block* generate(Simulation::Model *model);

        virtual void compute(Simulation::Context* context);

    public slots:
    };

}

#endif // VARSTATIC_H
