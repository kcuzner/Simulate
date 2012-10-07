#ifndef VARRAMP_H
#define VARRAMP_H

#include "../../Engine/simulation/block.h"
#include "../../Engine/simulation/context.h"

class VarRamp : public Simulation::Block
{
    Q_OBJECT

public:
    VarRamp(Simulation::Model* model);
};

#endif // VARRAMP_H
