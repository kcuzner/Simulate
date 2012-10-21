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

        virtual QObject* instance();

        virtual void initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context);

        virtual QStringList getOptionList();

        virtual QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context);

        virtual double getOption(const QString &name);
        virtual void setOption(const QString &name, const double value);

    signals:
        void addOutput(const QString&, int rank);
        void addInput(const QString&, int rank);
        void removeOutput(const QString&);
        void removeInput(const QString&);

    private:
        QSharedPointer<QHash<QString, double> > options;
    };

}

#endif // VARSTATIC_H
