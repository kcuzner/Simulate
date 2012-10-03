#ifndef SYSTEMBLOCKS_H
#define SYSTEMBLOCKS_H

#include <QtPlugin>
#include <QObject>

#include "../../Engine/simulation/blockplugin.h"
#include "SystemBlocks_global.h"

class SYSTEMBLOCKSSHARED_EXPORT SystemBlocks : public Simulation::BlockPlugin, public QObject
{

    Q_OBJECT
    Q_INTERFACES(Simulation::BlockPlugin)

public:
    SystemBlocks();

    void declareBlocks(Simulation::BlockFactory *factory);
};

#endif // SYSTEMBLOCKS_H
