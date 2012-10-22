#include "entryblock.h"

#include <QStringList>

using namespace Simulation;

EntryBlock::EntryBlock(Model *model, QString name) :
    Block(model, QSharedPointer<IBlockCore>())
{
    this->addOutput("Output");
    this->name = name;
}

QStringList EntryBlock::getOptionsList()
{
    QStringList options;
    options << "Value";
    return options;
}

void EntryBlock::execute(Context *context)
{
    double val = this->getOption("Value");
    QSharedPointer<QList<double> > values(new QList<double>());
    (*values) << val;
    this->setOutputValue(context, "Value", values);
}

QString EntryBlock::getName()
{
    return this->name;
}
