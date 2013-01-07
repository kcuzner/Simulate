#include "simulation.h"

Simulation::Simulation(int steps, double delta)
{
    this->setSteps(steps);
    this->setDelta(delta);

    this->simulationChanged = true;
}

Simulation::Simulation(int steps, double delta, const std::string &fileName)
{
    this->setSteps(steps);
    this->setDelta(delta);
    this->setFileName(fileName);

    this->simulationChanged = false;
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

bool Simulation::isChanged()
{
    return this->simulationChanged;
}

void Simulation::resetChanged()
{
    this->simulationChanged = false;
}

void Simulation::onBlockChanged(IModel *model, boost::shared_ptr<IBlock> block)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockChanged(this, modelPtr, block);
    }
}

void Simulation::onBlockConnected(IModel *model, boost::shared_ptr<IBlock> block, const std::string &output, boost::shared_ptr<IBlock> toBlock, const std::string &input)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockConnected(this, modelPtr, block, output, toBlock, input);
    }
}

void Simulation::onBlockOptionChanged(IModel *model, boost::shared_ptr<IBlock> block, const std::string &name)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockOptionChanged(this, modelPtr, block, name);
    }
}

void Simulation::onBlockDataChanged(IModel *model, boost::shared_ptr<IBlock> block, const std::string &name)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockDataChanged(this, modelPtr, block, name);
    }
}

void Simulation::onBlockInputAdded(IModel *model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockInput> input)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockInputAdded(this, modelPtr, block, input);
    }
}

void Simulation::onBlockInputRemoved(IModel *model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockInput> input)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockInputRemoved(this, modelPtr, block, input);
    }
}

void Simulation::onBlockOutputAdded(IModel *model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockOutput> output)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockOutputAdded(this, modelPtr, block, output);
    }
}

void Simulation::onBlockOutputRemoved(IModel *model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockOutput> output)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigBlockOutputRemoved(this, modelPtr, block, output);
    }
}

void Simulation::onModelChanged(IModel *model)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelChanged(this, modelPtr);
    }
}

void Simulation::onModelNameChanged(IModel *model, const std::string &name)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelNameChanged(this, modelPtr, name);
    }
}

void Simulation::onModelEntryAdded(IModel *model, boost::shared_ptr<IEntryBlock> entry)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelEntryAdded(this, modelPtr, entry);
    }
}

void Simulation::onModelEntryRemoved(IModel *model, boost::shared_ptr<IEntryBlock> entry)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelEntryRemoved(this, modelPtr, entry);
    }
}

void Simulation::onModelExitAdded(IModel *model, boost::shared_ptr<IExitBlock> exit)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelExitAdded(this, modelPtr, exit);
    }
}

void Simulation::onModelExitRemoved(IModel *model, boost::shared_ptr<IExitBlock> exit)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelExitRemoved(this, modelPtr, exit);
    }
}

void Simulation::onModelBlockAdded(IModel *model, boost::shared_ptr<IBlock> block)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelBlockAdded(this, modelPtr, block);
    }
}

void Simulation::onModelBlockRemoved(IModel *model, boost::shared_ptr<IBlock> block)
{
    if (this->models.count(model->getName()))
    {
        boost::shared_ptr<IModel> modelPtr = this->models.at(model->getName());

        this->sigModelBlockRemoved(this, modelPtr, block);
    }
}
