#ifndef VARRAMP_H
#define VARRAMP_H

#include "../../Engine/simulation/iblockcore.h"

class VarRamp : public QObject, Simulation::IBlockCore
{
    Q_OBJECT

    Q_INTERFACES(Simulation::IBlockCore)

public:
    explicit VarRamp(QObject* parent = 0);

    /**
     * @brief static generation method
     * @param parent
     * @return
     */
    static IBlockCore* generate(QObject* parent = 0);

    virtual QObject* instance();

    virtual void initialize(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > context);
    virtual QStringList getOptionList();
    virtual QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > execute(QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs, QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > >context);

    virtual double getOption(const QString &name);
    virtual void setOption(const QString &name, const double value);

signals:
    void addOutput(const QString&, int rank);
    void addInput(const QString&, int rank);
    void removeOutput(const QString&);
    void removeInput(const QString&);

private:
    QSharedPointer<QHash<QString, double> > options;
};

#endif // VARRAMP_H
