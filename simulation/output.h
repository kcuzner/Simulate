#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QSet>
#include <QString>
#include "context.h"
#include "signalvalue.h"

namespace Simulation
{
    class Block;
    class Input;

    /**
     * @brief Represents an output port on a block
     */
    class Output : public QObject
    {
        Q_OBJECT
    public:
        Output(Block *parent, QString name);

        ~Output();

        /**
         * @brief Returns the name of this port
         * @return
         */
        QString getName();

        /**
         * @brief Connects this output to an input
         * @param input
         */
        void connect(Input* input, bool backRef = true);
        /**
         * @brief Disconnects the passed input from this output
         * @param input
         */
        void disconnect(Input* input, bool backRef = true);

    signals:

    public slots:
        /**
         * @brief Sets the value of this output and runs the set method of all the attached input blocks
         * @param context Context to run in
         * @param value Value to set the inputs to
         */
        void set(Context* context, SignalValue value);

    protected:
        Block* block;
        QSet<Input*> connected;
        QString name;
    };

}

#endif // OUTPUT_H
