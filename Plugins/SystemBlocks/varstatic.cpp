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
    QList<Output*> outputs = this->getOutputs().values();

    double value = this->getOption("Value");

    Output* output;
    foreach(output, outputs)
    {
        output->set(context, context->createSignalValue(value));
    }
}

QStringList VarStatic::getOptionsList()
{
    QStringList ret;
    ret << "Value";

    return ret;
}

