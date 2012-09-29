#ifndef SIGNALVALUE_H
#define SIGNALVALUE_H

#include <vector>

namespace Simulation
{

    class SignalValue
    {
    public:
        SignalValue(double value);
        SignalValue(std::vector<double> values, int columns);

        double getValue(int index);
        double getValue(int column, int index);

        void redimension(int columns);

    protected:
        std::vector<double>* values;
        int columns;

    };

}

#endif // SIGNALVALUE_H
