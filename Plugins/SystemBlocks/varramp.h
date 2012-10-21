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

    virtual void initialize(QHash<QString, QList<double> > *context);
    virtual QStringList getOptionList();
    virtual QHash<QString, QList<double> > execute(QHash<QString, QList<double> > &inputs, QHash<QString, QList<double> > *context);

public slots:
    virtual void setOption(const QString &name, const QList<double> value);
};

#endif // VARRAMP_H
