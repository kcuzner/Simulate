#ifndef SYSTEMBLOCKS_H
#define SYSTEMBLOCKS_H

#include <QtPlugin>
#include <QObject>

#include "../../Engine/simulation/iblockplugin.h"
#include "SystemBlocks_global.h"

class SYSTEMBLOCKSSHARED_EXPORT SystemBlocks : public QObject, Simulation::IBlockPlugin
{

    Q_OBJECT
    Q_INTERFACES(Simulation::IBlockPlugin)

public:
    SystemBlocks();

    void declareBlocks(Simulation::BlockFactory *factory);
    QString getName();
    QString getDescription();
};

#endif // SYSTEMBLOCKS_H
