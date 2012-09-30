#ifndef SIGNALVALUE_H
#define SIGNALVALUE_H

#include <vector>

namespace Simulation
{

    /**
     * @brief The SignalValue class.
     *
     * References coming from outputs setting inputs are to be
     * valid for the duration of the context. References in a
     * context are kept until they are replaced by another value.
     */
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
