#include "systemblocks.h"

#include "varstatic.h"
#include "varramp.h"

#include "mathmultiply.h"
#include "mathintegrate.h"
#include "mathgain.h"

using namespace System;

SystemBlocks::SystemBlocks()
{
}

void SystemBlocks::declareToFactory(boost::shared_ptr<IBlockFactory> factory)
{
    factory->declareBlock(VarStatic::generate, "Var", "Static");
    factory->declareBlock(VarRamp::generate, "Var", "Ramp");

    factory->declareBlock(MathMultiply::generate, "Math", "Multiply");
    factory->declareBlock(MathIntegrate::generate, "Math", "Integrate");
    factory->declareBlock(MathGain::generate, "Math", "Gain");
}
