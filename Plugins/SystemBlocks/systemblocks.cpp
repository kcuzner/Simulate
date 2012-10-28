#include "systemblocks.h"

#include "varstatic.h"
#include "varramp.h"

using namespace Interfaces;

SystemBlocks::SystemBlocks()
{
}

void SystemBlocks::declareBlocks(IBlockFactory *factory)
{
    factory->declareBlock("Variables", "var.static", QIcon(), VarStatic::generate);
    factory->declareBlock("Variables", "var.ramp", QIcon(), VarRamp::generate);
}

QString SystemBlocks::getName()
{
    return "System Blocks";
}

QString SystemBlocks::getDescription()
{
    return "Base included system blocks for the Simulate engine. See LICENSE for licencing.";
}



Q_EXPORT_PLUGIN2(SystemBlocks, SystemBlocks)
