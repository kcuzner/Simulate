#include "varstatic.h"
#include "../../Engine/simulation/output.h"

#include <QStringList>

using namespace Blocks;
using namespace Simulation;

VarStatic::VarStatic(QObject *parent) : QObject(parent)
{
    this->options = QSharedPointer<QHash<QString, double> >(new QHash<QString, double>());
}

VarStatic::~VarStatic()
{
}

IBlockCore *VarStatic::generate(QObject *parent)
{
    return new VarStatic(parent);
}

QObject *VarStatic::instance()
{
    return this;
}

void VarStatic::initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context)
{
}

QStringList VarStatic::getOptionList()
{
    QStringList ret;
    ret << "Value";

    return ret;
}

QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > VarStatic::execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context)
{
}

double VarStatic::getOption(const QString &name)
{
    return (*this->options)[name];
}

void VarStatic::setOption(const QString &name, const double value)
{
    (*this->options)[name] = value;
}
