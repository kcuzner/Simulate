#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QList>
#include <QHash>
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
    public:
        explicit Context(Model* model, double timeStep, QObject *parent = 0);
        Context(Model* model, Context* parent);

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

        /**
         * @brief Creates a child context from this context
         * @return
         */
        Context* createChildContext(Model *model);

        /**
         * @brief Steps the blocks attached to this context
         */
        void step();


    signals:

    public slots:
        /**
         * @brief resets the context
         */
        void reset();
        /**
         * @brief Sets an input to a value in this context
         * @param input
         */
        void setInput(Input* input, SignalValue value);

    protected:
        /**
         * @brief Contains data for a block in this context
         */
        class BlockData
        {
        public:
            BlockData(Block* block);

            /**
             * @brief Resets the block values and input values
             */
            void reset();
            /**
             * @brief Resets the input values to null in preparation for a new step
             */
            void newStep();

            /**
             * @brief Sets a value for the block to persist between steps
             * @param valueName Name of the value to set
             * @param value Value to set it to
             */
            void setValue(QString valueName, SignalValue value);
            /**
             * @brief Returns a value by name
             * @param valueName Name of the value to get
             * @return
             */
            SignalValue getValue(QString valueName);

        protected:
            QHash<Input*, SignalValue> inputValues;
            QHash<QString, SignalValue> blockValues;
        };

        double timeStep;
        QList<Context*> children;
        /**
         * @brief Model this is attached to
         */
        Model* model;

    };

}

#endif // CONTEXT_H
