#include "varstatic.h"

using namespace Blocks;
using namespace Simulation;

VarStatic::VarStatic() :
    Block("var.static", &VarStatic::generate)
{
}

VarStatic::~VarStatic()
{
}

Block *VarStatic::generate()
{
    return new VarStatic();
}

void VarStatic::compute(Context *context)
{
}

