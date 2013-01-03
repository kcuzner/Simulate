#ifndef SIMULATION_H
#define SIMULATION_H

#include "interfaces/isimulation.h"

#include <map>

class Simulation : public ISimulation
{
public:
    Simulation(int steps, double delta);
    Simulation(int steps, double delta, const std::string& fileName);

    virtual bool isFileNameSet() const;
    virtual void setFileName(const std::string& fileName);
    virtual const std::string& getFileName() const;

    virtual int getSteps() const;
    virtual void setSteps(int steps);

    virtual double getDelta() const;
    virtual void setDelta(double delta);

    virtual boost::shared_ptr<IModel> getRootModel();
    virtual bool setRootModel(const std::string& name);

    virtual const std::map<std::string, boost::shared_ptr<IModel> >& getModels();

    virtual boost::shared_ptr<IModel> getModel(const std::string& name);

    virtual bool addModel(boost::shared_ptr<IModel> model);
    virtual bool removeModel(const std::string& name);

protected:
    std::map<std::string, boost::shared_ptr<IModel> > models;
    std::string rootModelName;

    bool fileNameSet;
    std::string fileName;
    int steps;
    double delta;
};

#endif // SIMULATION_H
