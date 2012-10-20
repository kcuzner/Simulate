#include "stepcontext.h"

#include "signalvalue.h"
#include "context.h"
#include "input.h"
#include "block.h"

using namespace Simulation;

StepContext::StepContext(Context *context) :
    QObject((QObject*)context)
{
}

SignalValue *StepContext::createSignalValue(double value)
{
    return new SignalValue(this, value);
}

SignalValue *StepContext::createSignalValue(std::vector<double> values, int columns)
{
    return new SignalValue(this, values, columns);
}

/*SignalValue *StepContext::getInputValue(Input *input)
{
    if (this->inputValues.contains(input))
    {
        return this->inputValues[input];
    }

    return NULL; //null value for inputs that aren't yet set
}*/

Context *StepContext::getContext()
{
    return this->context;
}

QList<double> *StepContext::getInputValue(IBlockCore *block, const QString &inputName)
{
}

void StepContext::setInput(Input *input, SignalValue *value)
{
    //when a input is set, we check to see if all the inputs are set for the input's block. If this is the case, we queue the block for execution
    this->inputValues[input] = value;

    QList<Input*> inputs = input->getBlock()->getInputs().values();
    for(QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        //if the value isn't in our input list, it isn't set
        if (!this->inputValues.contains((*i)))
        {
            return; //we are done here
        }
    }

    //if we made it this far, we get to queue the block for execution
    this->context->queueBlock(input->getBlock());
}

void StepContext::setOutputValue(IBlockCore *block, const QString &outputName, QList<double> value)
{
}
