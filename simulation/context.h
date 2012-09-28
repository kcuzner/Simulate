#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QList>

namespace Simulation
{

    /**
     * @brief A simulation context
     */
    class Context : public QObject
    {
        Q_OBJECT
    public:
        explicit Context(double timeStep, QObject *parent = 0);
        Context(Context* parent);

        /**
         * @brief Returns the timestep of this context
         * @return Timestep of this context
         */
        double getTimeStep();
        /**
         * @brief setTimeStep
         * @param timeStep
         */
        void setTimeStep(double timeStep);

        Context* createChildContext();

    protected:
        double timeStep;
        QList<Context*> children;

    signals:

    public slots:
        /**
         * @brief resets the context
         */
        void reset();

    };

}

#endif // CONTEXT_H
