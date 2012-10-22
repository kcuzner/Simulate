#ifndef IPLUGINBASE_H
#define IPLUGINBASE_H

#include <QString>
#include <QtPlugin>

class IPluginBase
{
public:
    virtual ~IPluginBase() {}

    virtual QString getName() = 0;
    virtual QString getDescription() = 0;
};

Q_DECLARE_INTERFACE(IPluginBase, "org.Simulate.PluginInterface/1.0")

#endif // IPLUGINBASE_H
