#ifndef SIGNALVALUE_H
#define SIGNALVALUE_H

#include <vector>
#include <QObject>

namespace Simulation
{

    class StepContext;

    /**
     * @brief The SignalValue class.
     *
     * References coming from outputs setting inputs are to be
     * valid for the duration of the context. References in a
     * context are kept until they are replaced by another value.
     */
    class SignalValue : public QObject
    {
        Q_OBJECT

    public:
        SignalValue(StepContext* context, double value);
        SignalValue(StepContext* context, std::vector<double> values, int columns);

        double getValue(int index);
        double getValue(int column, int index);

        void redimension(int columns);

    protected:
        std::vector<double>* values;
        int columns;

    };

}

#endif // SIGNALVALUE_H
