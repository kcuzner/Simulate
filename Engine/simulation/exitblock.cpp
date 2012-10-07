#include "exitblock.h"

#include <QStringList>

using namespace Simulation;

ExitBlock::ExitBlock(Model *model, QString name) :
    Block(model)
{
    this->addInput("Input");
    this->name = name;
}

QStringList ExitBlock::getOptionsList()
{
    return QStringList();
}

void ExitBlock::compute(StepContext *context)
{
}

QString ExitBlock::getName()
{
    return this->name;
}
