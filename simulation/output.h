#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>

namespace Simulation
{

    class Output : public QObject
    {
        Q_OBJECT
    public:
        explicit Output(QObject *parent = 0);

    signals:

    public slots:

    };

}

#endif // OUTPUT_H
