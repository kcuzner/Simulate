#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QRunnable>

#include "blockfactory.h"

namespace Simulation
{
    class Input;
    class Output;
    class Context;

    class Block : public QObject
    {
        Q_OBJECT

    public:
        Block(QString name, GenerateBlock generator, QObject *parent = 0);

        QHash<QString, Input*> getInputs();
        QHash<QString, Output*> getOutputs();

    signals:
        void inputAdded(Input*);
        void inputRemoved(Input*);
        void outputAdded(Output*);
        void outputRemoved(Output*);

    public slots:
        virtual void execute(Context* context) = 0;

    protected:
        Input* addInput(QString name);
        Output* addOutput(QString name);
        void removeInput(QString name);
        void removeInput(Input* input);
        void removeOutput(QString name);
        void removeOutput(Output* output);

    private:
        QHash<QString, Input*> inputs;
        QHash<QString, Output*> outputs;
    };

}

#endif // BLOCK_H
