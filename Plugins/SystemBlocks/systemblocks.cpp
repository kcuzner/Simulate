#include "systemblocks.h"

#include "varstatic.h"

using namespace Simulation;
using namespace Blocks;

SystemBlocks::SystemBlocks()
{
}

void SystemBlocks::declareBlocks(BlockFactory *factory)
{
    factory->declareBlock("var.static", VarStatic::generate);
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
