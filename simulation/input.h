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

    /**
     * @brief Represents an input to a block
     *
     * Inputs are connected to only one output block
     */
    class Input : public QObject
    {
        Q_OBJECT
    public:
        Input(Block *parent, QString name);

        ~Input();

        QString getName();

        /**
         * @brief isConnected returns true of this input is connected
         * @return
         */
        bool isConnected();

        /**
         * @brief Connects this input to the passed output, linking both directions
         * @param output
         */
        void connect(Output* output, bool backRef = true);
        /**
         * @brief Disconnects this input from the passed output, linking both directions
         * @param output
         */
        void disconnect(bool backRef = true);

    signals:
        void connected(Output*);
        void disconnected();

    public slots:
        void set(Context* context, SignalValue* value);

    protected:
        Block* block;
        Output* output; //the one and only output this is set by
        QString name;
    };

}

#endif // INPUT_H
