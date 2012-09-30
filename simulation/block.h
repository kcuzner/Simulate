#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QRunnable>

namespace Simulation
{
    class Input;
    class Output;
    class Context;

    class Block : public QObject, QRunnable
    {
        Q_OBJECT
    public:
        explicit Block(QObject *parent = 0);

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
        void removeOutput(Input* input);

    private:
        QHash<QString, Input*> inputs;
        QHash<QString, Output*> outputs;
    };

}

#endif // BLOCK_H
