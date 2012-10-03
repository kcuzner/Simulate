#include "varstatic.h"

using namespace Blocks;
using namespace Simulation;

VarStatic::VarStatic(Model* model) : Block(model)
{
}

VarStatic::~VarStatic()
{
}

Block *VarStatic::generate(Model* model)
{
    return new VarStatic(model);
}

void VarStatic::compute(Context *context)
{
}

