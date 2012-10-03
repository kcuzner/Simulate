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

Q_EXPORT_PLUGIN2(SystemBlocks, SystemBlocks)
