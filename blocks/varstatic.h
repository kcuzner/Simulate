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
        VarStatic();
        ~VarStatic();

        static Block* generate();

        virtual void compute(Simulation::Context* context);

    public slots:
    };

}

#endif // VARSTATIC_H
