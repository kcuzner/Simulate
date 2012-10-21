#ifndef IBLOCKCORE_H
#define IBLOCKCORE_H

#include <QString>
#include <QHash>
#include <QList>
#include <QStringList>
#include <QSharedPointer>

namespace Simulation
{
    /**
     * @brief Interface for the core component of a block which does computations and setup
     */
    class IBlockCore
    {
    public:
        virtual ~IBlockCore() {}

        /**
         * @brief Returns this IBlockCore as an instance
         * @return
         */
        virtual QObject* instance() = 0;

        /**
         * @brief initializes the block into the passed context of variables
         * @param context to modify to initial values
         */
        virtual void initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context) = 0;

        virtual QStringList getOptionList() = 0;

        /**
         * @brief executes the block's operation
         * @param inputs input values
         * @param context to modify with persistent variables
         * @return outputs
         */
        virtual QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context) = 0;

        virtual double getOption(const QString &name) = 0;
        virtual void setOption(const QString &name, const double value) = 0;

        /**
         * Implement the following signals and slots in an IBlockCore:
         */
    /*signals:
        void addOutput(const QString&, int rank);
        void addInput(const QString&, int rank);
        void removeOutput(const QString&);
        void removeInput(const QString&);
    */
    };
}

Q_DECLARE_INTERFACE(Simulation::IBlockCore, "org.Simulate.Engine.IBlockCore/1.0")

#endif // IBLOCKCORE_H
