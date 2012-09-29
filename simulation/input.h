#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QSet>
#include <QString>

#include "signalvalue.h"
#include "context.h"

namespace Simulation
{
    class Block;
    class Output;

    class Input : public QObject
    {
        Q_OBJECT
    public:
        Input(Block *parent, QString name);

        ~Input();

        QString getName();

        /**
         * @brief Connects this input to the passed output, linking both directions
         * @param output
         */
        void connect(Output* output, bool backRef = true);
        /**
         * @brief Disconnects this input from the passed output, linking both directions
         * @param output
         */
        void disconnect(Output* output, bool backRef = true);

    signals:

    public slots:
        void set(Context* context, SignalValue value);

    protected:
        Block* block;
        QSet<Output*> connected;
        QString name;
    };

}

#endif // INPUT_H
