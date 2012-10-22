#include "exitblock.h"

#include <QStringList>

using namespace Simulation;

ExitBlock::ExitBlock(Model *model, QString name) :
    Block(model, QSharedPointer<IBlockCore>())
{
    this->addInput("Input");
    this->name = name;
}

QStringList ExitBlock::getOptionsList()
{
    return QStringList();
}

void ExitBlock::compute(Context*)
{
    //nothing to do here...
}

QString ExitBlock::getName()
{
    return this->name;
}
