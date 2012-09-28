#ifndef SIGNALVALUE_H
#define SIGNALVALUE_H

#include <QObject>
#include <QVector>

namespace Simulation
{

    class SignalValue : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructs this SignalValue as a scalar
         * @param value Scalar value
         * @param parent Parent QObject
         */
        explicit SignalValue(double value, QObject *parent = 0);
        /**
         * @brief Constructs this SignalValue as a matrix
         * @param values Vector of values to start this off with
         * @param columns Number of columns to create
         * @param parent Parent QObject
         */
        explicit SignalValue(QVector<double> values, int columns = 1, QObject *parent = 0);

        ~SignalValue();

        /**
         * @brief Returns a value from this signal
         * @param index Index in the underlying vector to grab from
         */
        double getValue(int index = 0);
        /**
         * @brief Returns a value from this signal
         * @param column Column number to pull from
         * @param index Index in the column
         */
        double getValue(int column, int index = 0);

    signals:

    public slots:
        /**
         * @brief Redimensions this SignalValue to be a vector
         * @param Dimensions to use
         */
        void redimension(int dimensions);


    protected:
        /**
         * @brief Dimension of this signal value
         */
        int dimension;
        /**
         * @brief Vector of values in this signal value
         */
        QVector<double>* values;


    };

}

#endif // SIGNALVALUE_H
