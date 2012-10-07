#include "signalvalue.h"

#include "stepcontext.h"

#include <stdexcept>

using namespace Simulation;

SignalValue::SignalValue(StepContext *context, double value)
{
    this->values = new std::vector<double>(1, value);
    this->redimension(1);
}

SignalValue::SignalValue(StepContext *context,std::vector<double> values, int columns)
{
    this->values = new std::vector<double>(values);
    this->redimension(columns);
}

double SignalValue::getValue(int index)
{
    return this->values->at(index);
}

double SignalValue::getValue(int column, int index)
{
    int cLength = this->values->size() / this->columns;
    return this->values->at(column * cLength + index);
}

void SignalValue::redimension(int columns)
{
    if (this->values->size() % columns != 0)
    {
        throw new std::out_of_range("columns");
    }
}
