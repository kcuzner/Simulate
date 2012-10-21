#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QSet>
#include <QString>

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

        Q_PROPERTY(QString Name READ getName)
        Q_PROPERTY(Block* Block READ getBlock)

    public:
        Input(Block *parent, QString name);

        ~Input();

        QString getName();
        QSharedPointer<QList<double> > getValue(Context* context);
        Block* getBlock();

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

    protected:
        Block* block;
        Output* output; //the one and only output this is set by
        QString name;
    };

}

#endif // INPUT_H
