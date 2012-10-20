#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QQueue>
#include "signalvalue.h"

namespace Simulation
{
    class Input;
    class Block;
    class Model;

    /**
     * @brief A simulation context
     */
    class Context : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(double TimeStep READ getTimeStep WRITE setTimeStep)

    public:
        explicit Context(Model* model, double timeStep, QObject *parent = 0);
        Context(Model* model, Context* parent);

        /**
         * @brief Returns the timestep of this context
         * @return Timestep of this context
         */
        double getTimeStep();

        /**
         * @brief Creates a child context from this context
         * @return
         */
        Context* createChildContext(Model *model);

        /**
         * @brief isBlockReady called by inputs to determine if the block should be queued
         * @param block
         * @return
         */
        bool isBlockReady(Block* block);

        /**
         * @brief getInputValue returns the current value of an input in this context
         * @param input
         * @return
         */
        SignalValue* getInputValue(Input* input);


    signals:
        void finished(int steps);

    public slots:
        /**
         * @brief resets the context
         */
        void reset();
        /**
         * @brief Sets an input to a value in this context
         * @param input
         */
        void setInput(Input* input, SignalValue* value);
        /**
         * @brief setTimeStep
         * @param timeStep
         */
        void setTimeStep(double timeStep);
        void queueBlock(Block* block);
        /**
         * @brief Steps the blocks attached to this context
         */
        void step();

    protected:
        /**
         * @brief Initializes the blocks attached to the model in this context
         */
        void initialize();

        double timeStep;
        QList<Context*> children;
        /**
         * @brief Model this is attached to
         */
        Model* model;
        QQueue<Block*> execute;
        QList<Block*>::iterator current;

    };

}

#endif // CONTEXT_H
