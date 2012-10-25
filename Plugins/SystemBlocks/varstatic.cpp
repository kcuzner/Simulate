#include "varstatic.h"
#include "../../Engine/simulation/output.h"

#include <QStringList>

using namespace Simulation;

VarStatic::VarStatic(QObject *parent) : QObject(parent)
{
    this->options = QSharedPointer<QHash<QString, double> >(new QHash<QString, double>());
    emit(this->addOutput("Output", 0));
}

VarStatic::~VarStatic()
{
}

Interfaces::IBlockCore *VarStatic::generate(QObject *parent)
{
    return new VarStatic(parent);
}

QObject *VarStatic::instance()
{
    return this;
}

void VarStatic::initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > >)
{
}

QStringList VarStatic::getOptionList()
{
    QStringList ret;
    ret << "Value";

    return ret;
}

QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > VarStatic::execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > , QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > )
{
    QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > outputs(new QHash<QString, QSharedPointer<QList<double> > >());

    QSharedPointer<QList<double> > valueList(new QList<double>());
    double value = this->getOption("Value");
    (*valueList) << value;

    (*outputs)["Output"] = valueList;

    return outputs;
}

double VarStatic::getOption(const QString &name)
{
    return (*this->options)[name];
}

void VarStatic::setOption(const QString &name, const double value)
{
    (*this->options)[name] = value;
}
