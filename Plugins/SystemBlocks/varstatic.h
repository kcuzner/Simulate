#ifndef VARSTATIC_H
#define VARSTATIC_H

#include "../../Engine/simulation/iblockcore.h"

namespace Blocks
{

    class VarStatic : public QObject, Simulation::IBlockCore
    {
        Q_OBJECT

        Q_INTERFACES(Simulation::IBlockCore)

    public:
        VarStatic(QObject* parent = 0);
        ~VarStatic();

        static IBlockCore* generate(QObject* parent = 0);

        virtual void initialize(QHash<QString, QList<double> > *context);

        virtual QStringList getOptionList();

        virtual QHash<QString, QList<double> > execute(QHash<QString, QList<double> > &inputs, QHash<QString, QList<double> > *context);

    public slots:
        virtual void setOption(const QString &name, const QList<double> value);
    };

}

#endif // VARSTATIC_H
