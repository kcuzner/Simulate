#ifndef IBLOCKVISUAL_H
#define IBLOCKVISUAL_H

#include <QList>
#include <QPoint>
#include <QIcon>
#include <QPainter>

namespace Simulation
{
    /**
     * @brief Interface for the visual aspect of a block
     */
    class IBlockVisual
    {
    public:
        virtual ~IBlockVisual() {}

        virtual QList<QPoint> getInputPositions(int numInputs) = 0;
        virtual QList<QPoint> getOutputPoisitions(int numOutputs) = 0;
        virtual QIcon getIcon() = 0;
        virtual QSize getSize() = 0;
        virtual void draw(QPainter* painter) = 0;

    };
}

Q_DECLARE_INTERFACE(Simulation::IBlockVisual, "org.Simulate.Engine.IBlockVisual/1.0")

#endif // IBLOCKVISUAL_H
