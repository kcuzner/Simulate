#ifndef SYSTEMBLOCKS_H
#define SYSTEMBLOCKS_H

#include <QtPlugin>
#include <QObject>

#include "../../Engine/interfaces/iblockplugin.h"
#include "SystemBlocks_global.h"

class SYSTEMBLOCKSSHARED_EXPORT SystemBlocks : public QObject, public Interfaces::IBlockPlugin
{

    Q_OBJECT
    Q_INTERFACES(Interfaces::IBlockPlugin)

public:
    SystemBlocks();

    void declareBlocks(Interfaces::IBlockFactory *factory);
    QString getName();
    QString getDescription();
};

#endif // SYSTEMBLOCKS_H
