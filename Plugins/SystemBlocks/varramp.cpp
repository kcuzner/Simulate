#include "varramp.h"

using namespace Interfaces;

VarRamp::VarRamp(QObject *parent)
    : QObject(parent)
{
    this->options = QSharedPointer<QHash<QString, double> >(new QHash<QString, double>);
}

IBlockCore *VarRamp::generate(QObject *parent)
{
    return new VarRamp(parent);
}

QObject *VarRamp::instance()
{
    return this;
}

void VarRamp::initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context)
{
}

QStringList VarRamp::getOptionList()
{
    QStringList options;
    options << "Initial Value"
            << "Initial/Final Slope"
            << "Final Value"
            << "Final/Initial Slope";
    return options;
}

QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > VarRamp::execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context)
{
}

double VarRamp::getOption(const QString &name)
{
    return (*this->options)[name];
}

void VarRamp::setOption(const QString &name, const double value)
{
    (*this->options)[name] = value;
}
