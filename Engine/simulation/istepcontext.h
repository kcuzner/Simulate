#ifndef ISTEPCONTEXT_H
#define ISTEPCONTEXT_H

#include <QtPlugin>

#include <QList>

namespace Simulation
{
    class IBlockCore;

    class IStepContext
    {
    public:
        virtual ~IStepContext() {}

        virtual QList<double>* getInputValue(IBlockCore* block, const QString& inputName) = 0;

    public slots:
        virtual void setOutputValue(Simulation::IBlockCore* block, const QString& outputName, QList<double> value) = 0;

    };
}

Q_DECLARE_INTERFACE(Simulation::IStepContext, "org.Simulate.Engine.IStepContext/1.0")

#endif // ISTEPCONTEXT_H
