#include "signalvalue.h"

#include <stdexcept>

using namespace std;
using namespace Simulation;

SignalValue::SignalValue(double value, QObject *parent) :
    QObject(parent)
{
    this->values = new QVector<double>(1, value);
    this->redimension(1);
}


SignalValue::SignalValue(QVector<double> values, int columns, QObject *parent) :
    QObject(parent)
{
    this->values = new QVector<double>(values);
    this->redimension(columns);
}

SignalValue::~SignalValue()
{
    if (this->values != NULL)
    {
        delete this->values; //clean up
    }
}

double SignalValue::getValue(int index)
{
    return this->values->at(index);
}

double SignalValue::getValue(int column, int index)
{
    return this->values->at(column * this->dimension + index);
}

void SignalValue::redimension(int dimensions)
{
    //check the value length to make sure it can be dimensioned to this length
    if (this->values->size() % dimensions == 0)
    {
        //if we can't divide the dimension into the size of the
        //vector evenly, it is not able to be dimensioned to this dimension
        throw new std::out_of_range("dimensions");
    }
    this->dimension = dimensions;
}
