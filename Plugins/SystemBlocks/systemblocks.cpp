#include "systemblocks.h"

#include "varstatic.h"
#include "varramp.h"

using namespace Interfaces;

SystemBlocks::SystemBlocks()
{
}

void SystemBlocks::declareBlocks(IBlockFactory *factory)
{
    factory->declareBlock("System", "var.static", VarStatic::generate);
    factory->declareBlock("System", "var.ramp", VarRamp::generate);
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
