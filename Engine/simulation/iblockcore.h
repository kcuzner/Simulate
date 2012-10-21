#ifndef IBLOCKCORE_H
#define IBLOCKCORE_H

#include <QString>
#include <QHash>
#include <QList>
#include <QStringList>

namespace Simulation
{
    class IBlockCore
    {
    public:
        virtual ~IBlockCore() {}

        /**
         * @brief initializes the block into the passed context of variables
         * @param context to modify to initial values
         */
        virtual void initialize(QHash<QString, QList<double> >* context) = 0;

        virtual QStringList getOptionList() = 0;

        /**
         * @brief executes the block's operation
         * @param inputs input values
         * @param context to modify with persistent variables
         * @return outputs
         */
        virtual QHash<QString, QList<double> > execute(QHash<QString, QList<double> >& inputs, QHash<QString, QList<double> >* context) = 0;

    signals:
        void addOutput(const QString&, int rank);
        void addInput(const QString&, int rank);
        void removeOutput(const QString&);
        void removeInput(const QString&);

    public slots:
        virtual void setOption(const QString& name, const QList<double> value) = 0;
    };
}

Q_DECLARE_INTERFACE(Simulation::IBlockCore, "org.Simulate.Engine.IBlockCore/1.0")

#endif // IBLOCKCORE_H
