#ifndef ENGINE_H
#define ENGINE_H

#include "interfaces/iengine.h"
#include "interfaces/iblockfactory.h"
#include "interfaces/icontext.h"

#include <boost/smart_ptr.hpp>

class SimpleEngine : IEngine
{
public:
    SimpleEngine(int steps, double delta);

    virtual int getStepsToRun();
    virtual void setStepsToRun(int n);

    virtual double getStepDelta();
    virtual void setStepDelta(double d);

    virtual void run(boost::shared_ptr<IModel> model);

    virtual boost::shared_ptr<IBlockFactory> getBlockFactory();

protected:
    int steps;
    double delta;
    boost::shared_ptr<IBlockFactory> factory;

    boost::shared_ptr<IContext> setup(boost::shared_ptr<IModel> model);
};

#endif // ENGINE_H
