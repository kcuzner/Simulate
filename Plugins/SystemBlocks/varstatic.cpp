#include "varstatic.h"
#include "../../Engine/simulation/output.h"
#include "../../Engine/simulation/stepcontext.h"

#include <QStringList>

using namespace Blocks;
using namespace Simulation;

VarStatic::VarStatic(Model* model) : Block(model)
{
    this->addOutput("Value");
}

VarStatic::~VarStatic()
{
}

Block *VarStatic::generate(Model* model)
{
    return new VarStatic(model);
}

void VarStatic::compute(StepContext *context)
{
    QHash<QString, Output*> outputs = this->getOutputs();
}

QStringList VarStatic::getOptionsList()
{
    QStringList ret;
    ret << "Value";

    return ret;
}

