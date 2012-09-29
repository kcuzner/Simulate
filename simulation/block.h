#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QString>
#include <QHash>

namespace Simulation
{
    class Input;
    class Output;

    class Block : public QObject
    {
        Q_OBJECT
    public:
        explicit Block(QObject *parent = 0);

    signals:

    public slots:

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
