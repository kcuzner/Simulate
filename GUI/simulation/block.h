#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QRunnable>
#include <QtPlugin>
#include <QUuid>

#include "context.h"
#include "model.h"
#include "../interfaces/iblockcore.h"

namespace Simulation
{
    class Input;
    class Output;
    class StepContext;

    class Block : public QObject
    {
        Q_OBJECT

    public:
        Block(Model* model, QSharedPointer<Interfaces::IBlockCore> core);
        ~Block();

        QHash<QString, QSharedPointer<Input> > getInputs();
        QHash<QString, QSharedPointer<Output> > getOutputs();

        virtual QStringList getOptionsList();
        virtual double getOption(const QString &name);

        QUuid getUUid();

    signals:
        void inputAdded(QSharedPointer<Input>);
        void inputRemoved(QSharedPointer<Input>);
        void outputAdded(QSharedPointer<Output>);
        void outputRemoved(QSharedPointer<Output>);

    public slots:
        virtual void initialize(Context* context);
        virtual void execute(Context* context);
        virtual void setOption(const QString& name, double value);

    protected slots:
        void coreInputAdded(const QString& name, int rank);
        void coreOutputAdded(const QString& name, int rank);
        void coreInputRemoved(const QString& name);
        void coreOutputRemoved(const QString& name);
        void setOutputValue(Context *context, const QString& name, QSharedPointer<QList<double> > value);

    protected:
        QSharedPointer<Input> addInput(const QString& name);
        QSharedPointer<Output> addOutput(const QString& name);
        void removeInput(const QString& name);
        void removeInput(QSharedPointer<Input> input);
        void removeOutput(const QString& name);
        void removeOutput(QSharedPointer<Output> output);

        QSharedPointer<Interfaces::IBlockCore> core;

    private:
        QUuid uuid;
        QSharedPointer<QHash<QString, QSharedPointer<Input> > > inputs;
        QSharedPointer<QHash<QString, QSharedPointer<Output> > > outputs;
        QSharedPointer<QHash<QString, double> > options;
    };

}

#endif // BLOCK_H
