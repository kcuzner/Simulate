#ifndef STEPCONTEXT_H
#define STEPCONTEXT_H

#include <QObject>
#include <QHash>
#include <vector>

namespace Simulation
{
    class SignalValue;
    class Context;
    class Block;
    class Input;

    /**
     * @brief A step context is used as the parent of all signal values used during a step
     *
     * Its main purpose in life is to simply be a memory management go-between
     * for the context.
     */
    class StepContext : public QObject
    {
        Q_OBJECT
    public:
        StepContext(Context *context);

        SignalValue* createSignalValue(double value);
        SignalValue* createSignalValue(std::vector<double> values, int columns);

        SignalValue* getInputValue(Input* input);

        Context* getContext();

    signals:

    public slots:
        void setInput(Input* input, SignalValue* value);

    protected:
        Context* context;

        QHash<Input*, SignalValue*> inputValues;

    };
}

#endif // STEPCONTEXT_H
