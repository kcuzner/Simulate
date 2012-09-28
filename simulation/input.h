#ifndef INPUT_H
#define INPUT_H

#include <QObject>

namespace Simulation
{

    class Input : public QObject
    {
        Q_OBJECT
    public:
        explicit Input(QObject *parent = 0);

    signals:

    public slots:

    };

}

#endif // INPUT_H
