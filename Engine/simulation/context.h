#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QQueue>
#include <QSharedPointer>

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
         * @brief Returns the context used by a block for storing persistant variables for this context
         * @param instance
         * @return Persistant variable hash
         */
        QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > getPersistantBlockContext(Block* instance);

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
        QSharedPointer<QList<double> > getInputValue(Input* input);

        QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > getBlockInputs(Block* instance);


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
        void setInput(Input* input, QSharedPointer<QList<double> > value);
        /**
         * @brief setTimeStep
         * @param timeStep
         */
        void setTimeStep(double timeStep);
        void queueBlock(QSharedPointer<Block> block);
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
        QQueue<QSharedPointer<Block> > execute;
        QList<QSharedPointer<Block> >::iterator current;

        QHash<Block*, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > > variableContexts;
        QHash<Input*, QSharedPointer<QList<double> > > inputValues;

    };

}

#endif // CONTEXT_H
