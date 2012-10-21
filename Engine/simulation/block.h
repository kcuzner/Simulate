#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QRunnable>
#include <QtPlugin>

#include "blockfactory.h"
#include "context.h"
#include "model.h"
#include "iblockcore.h"

namespace Simulation
{
    class Input;
    class Output;
    class StepContext;

    class Block : public QObject
    {
        Q_OBJECT

    public:
        Block(Model* model, QSharedPointer<IBlockCore> core);
        ~Block();

        QHash<QString, Input*> getInputs();
        QHash<QString, Output*> getOutputs();

        virtual QStringList getOptionsList();
        double getOption(const QString &name);

        virtual void compute(StepContext* context);

    signals:
        void inputAdded(Input*);
        void inputRemoved(Input*);
        void outputAdded(Output*);
        void outputRemoved(Output*);

    public slots:
        void initialize(Context* context);
        void execute(StepContext* context);
        void setOption(const QString& name, double value);

    protected slots:
        void coreInputAdded(const QString& name, int rank);
        void coreOutputAdded(const QString& name, int rank);
        void coreInputRemoved(const QString& name);
        void coreOutputRemoved(const QString& name);

    protected:
        Input* addInput(QString name);
        Output* addOutput(QString name);
        void removeInput(QString name);
        void removeInput(Input* input);
        void removeOutput(QString name);
        void removeOutput(Output* output);

        QSharedPointer<IBlockCore> core;

    private:
        QHash<QString, Input*> inputs;
        QHash<QString, Output*> outputs;
    };

}

#endif // BLOCK_H
