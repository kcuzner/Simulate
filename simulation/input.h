#ifndef INPUT_H
#define INPUT_H

#include <QObject>

#include "signalvalue.h"
#include "context.h"

namespace Simulation
{

    class Input : public QObject
    {
        Q_OBJECT
    public:
        explicit Input(QObject *parent = 0);

    signals:

    public slots:
        void set(Context* context, SignalValue value);
    };

}

#endif // INPUT_H
