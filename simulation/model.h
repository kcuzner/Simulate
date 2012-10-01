#ifndef MODEL_H
#define MODEL_H

#include <QObject>

namespace Simulation
{
    class Block;

    class Model : public QObject
    {
        Q_OBJECT
    public:
        explicit Model(QObject *parent = 0);

    signals:

    public slots:

    protected:
        QList<Block*> blocks;

    };

}

#endif // MODEL_H
