#include "entryblock.h"

#include <QStringList>

using namespace Simulation;

EntryBlock::EntryBlock(Model *model, QString name) :
    Block(model)
{
    this->addOutput("Output");
    this->name = name;
}

QStringList EntryBlock::getOptionsList()
{
    return QStringList();
}

void EntryBlock::compute(StepContext *context)
{
}

QString EntryBlock::getName()
{
    return this->name;
}
