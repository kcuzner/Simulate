#ifndef IBLOCKFACTORY_H
#define IBLOCKFACTORY_H

#include "iblockcore.h"

#include <QObject>
#include <QString>
#include <QIcon>
#include <QUuid>

namespace Interfaces
{
    typedef IBlockCore* (*GenerateBlock)(QObject*);

    class IBlockFactory
    {
    public:
        virtual ~IBlockFactory() {}

        /**
         * @brief declareBlock
         * @param group Toolbox group this should belong to
         * @param name Name of the block
         * @param generator
         * @return Name of this block
         */
        virtual int declareBlock(QString group, QString name, QIcon icon, GenerateBlock generator) = 0;
    };
}

Q_DECLARE_INTERFACE(Interfaces::IBlockFactory, "org.Simulate.Engine.IBlockFactory/1.0")

#endif // IBLOCKFACTORY_H
