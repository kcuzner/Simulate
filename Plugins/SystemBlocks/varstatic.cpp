#include "varstatic.h"
#include "../../Engine/simulation/output.h"
#include "../../Engine/simulation/stepcontext.h"

#include <QStringList>

using namespace Blocks;
using namespace Simulation;

VarStatic::VarStatic(QObject *parent) : QObject(parent)
{
}

VarStatic::~VarStatic()
{
}

IBlockCore *VarStatic::generate(QObject *parent)
{
    return new VarStatic(parent);
}

QStringList VarStatic::getOptionList()
{
    QStringList ret;
    ret << "Value";

    return ret;
}


QHash<QString, QList<double> > VarStatic::execute(QHash<QString, QList<double> > &inputs, QHash<QString, QList<double> > *context)
{
}

void VarStatic::setOption(const QString &name, const QList<double> value)
{
}
