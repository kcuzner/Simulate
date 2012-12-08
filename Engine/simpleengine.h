#ifndef ENGINE_H
#define ENGINE_H

#include "interfaces/iengine.h"
#include "interfaces/iblockfactory.h"
#include "interfaces/icontext.h"

#include <boost/smart_ptr.hpp>

class SimpleEngine : IEngine
{
public:
    SimpleEngine();

    boost::shared_ptr<IBlockFactory> getBlockFactory();
    void setBlockFactory(boost::shared_ptr<IBlockFactory> factory);

    boost::shared_ptr<IContext> createContext();
    void setContextCreator(boost::function<boost::shared_ptr<IContext> ()> generator);

protected:
    boost::shared_ptr<IBlockFactory> currentFactory;
    boost::function<boost::shared_ptr<IContext> ()> contextGenerator;

    boost::shared_ptr<IContext> generateDefaultContext();
};

#endif // ENGINE_H
