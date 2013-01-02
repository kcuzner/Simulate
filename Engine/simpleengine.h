#ifndef ENGINE_H
#define ENGINE_H

#include "interfaces/iengine.h"
#include "interfaces/iblockfactory.h"
#include "interfaces/icontext.h"

#include <boost/smart_ptr.hpp>

class SimpleEngine : public IEngine
{
public:
    static boost::shared_ptr<IEngine> generate(boost::shared_ptr<IModel> model, int steps, double delta);

    virtual unsigned int getStepsToRun();
    virtual void setStepsToRun(unsigned int n);

    virtual double getStepDelta();
    virtual void setStepDelta(double d);

    virtual boost::shared_ptr<IContext> getContext();

    virtual boost::shared_ptr<IModel> getRootModel();

    virtual void run();

    virtual boost::shared_ptr<IBlockFactory> getBlockFactory();

protected:
    unsigned int steps;
    double delta;
    boost::shared_ptr<IModel> model;
    boost::shared_ptr<IContext> context;
    boost::shared_ptr<IBlockFactory> factory;

private:
    SimpleEngine(boost::shared_ptr<IModel> model, int steps, double delta);
};

#endif // ENGINE_H
