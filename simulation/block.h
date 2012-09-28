#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>

namespace Simulation
{

    class Block : public QObject
    {
        Q_OBJECT
    public:
        explicit Block(QObject *parent = 0);

    signals:

    public slots:

    };

}

#endif // BLOCK_H
