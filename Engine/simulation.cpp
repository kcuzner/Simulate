#include "simulation.h"

Simulation::Simulation(int steps, double delta)
{
    this->setSteps(steps);
    this->setDelta(delta);
}

Simulation::Simulation(int steps, double delta, const std::string &fileName)
{
    this->setSteps(steps);
    this->setDelta(delta);
    this->setFileName(fileName);
}

bool Simulation::isFileNameSet() const
{
    return this->fileNameSet;
}

void Simulation::setFileName(const std::string &fileName)
{
    this->fileNameSet = true;
    this->fileName = fileName;
}

const std::string &Simulation::getFileName() const
{
    return this->fileName;
}

int Simulation::getSteps() const
{
    return this->steps;
}

void Simulation::setSteps(int steps)
{
    this->steps = steps;
}

double Simulation::getDelta() const
{
    return this->delta;
}

void Simulation::setDelta(double delta)
{
    this->delta = delta;
}

boost::shared_ptr<IModel> Simulation::getRootModel()
{
    if (this->models.count(this->rootModelName))
        return this->models.at(this->rootModelName);

    return boost::shared_ptr<IModel>();
}

bool Simulation::setRootModel(const std::string &name)
{
    if (this->models.count(name))
    {
        this->rootModelName = name;
        return true;
    }

    return false;
}

const std::map<std::string, boost::shared_ptr<IModel> > &Simulation::getModels()
{
    return this->models;
}

boost::shared_ptr<IModel> Simulation::getModel(const std::string &name)
{
    return this->models.at(name);
}

bool Simulation::addModel(boost::shared_ptr<IModel> model)
{
    if (this->models.count(model->getName()))
        return false; //already added a model by this name

    this->models[model->getName()] = model;

    return true;
}

bool Simulation::removeModel(const std::string &name)
{
    if (!this->models.count(name))
        return false;

    this->models.erase(name);

    return true;
}
