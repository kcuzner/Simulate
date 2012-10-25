#ifndef IBLOCKFACTORY_H
#define IBLOCKFACTORY_H

#include "iblockcore.h"

#include <QObject>
#include <QString>

namespace Interfaces
{
    typedef IBlockCore* (*GenerateBlock)(QObject*);

    class IBlockFactory
    {
    public:
        virtual ~IBlockFactory() {}

        virtual void declareBlock(QString name, GenerateBlock generator) = 0;
    };
}

Q_DECLARE_INTERFACE(Interfaces::IBlockFactory, "org.Simulate.Engine.IBlockFactory/1.0")

#endif // IBLOCKFACTORY_H
