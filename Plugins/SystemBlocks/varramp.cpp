#include "varramp.h"

using namespace Simulation;

VarRamp::VarRamp(QObject *parent)
    : QObject(parent)
{
}

IBlockCore *VarRamp::generate(QObject *parent)
{
    return new VarRamp(parent);
}

void VarRamp::initialize(QHash<QString, QList<double> > *context)
{
}

QStringList VarRamp::getOptionList()
{
}


QHash<QString, QList<double> > VarRamp::execute(QHash<QString, QList<double> > &inputs, QHash<QString, QList<double> > *context)
{
}

void VarRamp::setOption(const QString &name, const QList<double> value)
{
}
