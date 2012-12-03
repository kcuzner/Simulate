#include "modelblock.h"

ModelBlock::ModelBlock(int id, boost::shared_ptr<IModel> model)
{
    this->id = id;
    this->model = model;

    model->sigEntryAdded.connect(boost::bind(&ModelBlock::entryAdded, this, _1));
    model->sigEntryRemoved.connect(boost::bind(&ModelBlock::entryRemoved, this, _1));
    model->sigExitAdded.connect(boost::bind(&ModelBlock::exitAdded, this, _1));
    model->sigExitRemoved.connect(boost::bind(&ModelBlock::exitRemoved, this, _1));

    //inspect the model's entries and exits and create corrisponding inputs and
    //outputs except in the case that an entry and exit have the same name
    std::map<std::string, boost::shared_ptr<IEntryBlock> > entries = model->getEntries();
    std::map<std::string, boost::shared_ptr<IExitBlock> > exits = model->getExits();
}

int ModelBlock::getId()
{
    return this->id;
}

std::string ModelBlock::getGroup()
{
    return "engine";
}

std::string ModelBlock::getName()
{
    return "model";
}

const std::vector<double>& ModelBlock::getOption(const std::string &name)
{
}

void ModelBlock::setOption(const std::string &name, const std::vector<double>& value)
{
}

void ModelBlock::initialize(boost::shared_ptr<IContext> context)
{
}

void ModelBlock::execute(boost::shared_ptr<IContext> context, double delta)
{
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ModelBlock::getInputs()
{
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ModelBlock::getOutputs()
{
}

boost::shared_ptr<IModel> ModelBlock::getModel()
{
    return this->model;
}

void ModelBlock::entryAdded(boost::shared_ptr<IEntryBlock> entry)
{

}

void ModelBlock::entryRemoved(boost::shared_ptr<IEntryBlock> entry)
{
}

void ModelBlock::exitAdded(boost::shared_ptr<IExitBlock> exit)
{
}

void ModelBlock::exitRemoved(boost::shared_ptr<IExitBlock> exit)
{
}
