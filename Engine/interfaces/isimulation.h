#ifndef ISIMULATION_H
#define ISIMULATION_H

#include <boost/smart_ptr.hpp>

#include "iengine.h"

/**
 * @brief Class containing an engine and other such things which
 * is created from a file
 */
class ISimulation
{
public:
    virtual ~ISimulation() {}

    virtual bool isFileNameSet() const = 0;
    virtual void setFileName(const std::string& fileName) = 0;
    virtual const std::string& getFileName() const = 0;

    virtual int getSteps() const = 0;
    virtual void setSteps(int steps) = 0;

    virtual double getDelta() const = 0;
    virtual void setDelta(double delta) = 0;

    virtual boost::shared_ptr<IModel> getRootModel() = 0;
    virtual bool setRootModel(const std::string& name) = 0;

    virtual const std::map<std::string, boost::shared_ptr<IModel> >& getModels() = 0;

    virtual boost::shared_ptr<IModel> getModel(const std::string& name) = 0;

    virtual bool addModel(boost::shared_ptr<IModel> model) = 0;
    virtual bool removeModel(const std::string& name) = 0;
};

#endif // ISIMULATION_H
