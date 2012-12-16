#include "modelblock.h"

#include "baseblockinput.h"
#include "baseblockoutput.h"

ModelBlock::ModelBlock(long id, boost::shared_ptr<IModel> model)
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

    std::map<std::string, boost::shared_ptr<IEntryBlock> >::iterator enIter;
    for(enIter = entries.begin(); enIter != entries.end(); enIter++)
    {
        this->entryAdded((*enIter).second);
    }
    std::map<std::string, boost::shared_ptr<IExitBlock> >::iterator exIter;
    for(exIter = exits.begin(); exIter != exits.end(); exIter++)
    {
        this->exitAdded((*exIter).second);
    }
}

long ModelBlock::getId()
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

void ModelBlock::execute(IContext *context, double delta)
{
}

const std::map<std::string, boost::shared_ptr<IBlockInput> > &ModelBlock::getInputs()
{
    return this->inputs;
}

const std::map<std::string, boost::shared_ptr<IBlockOutput> > &ModelBlock::getOutputs()
{
    return this->outputs;
}

boost::shared_ptr<IModel> ModelBlock::getModel()
{
    return this->model;
}

void ModelBlock::entryAdded(boost::shared_ptr<IEntryBlock> entry)
{
    //add an input to match this entry
    boost::shared_ptr<BaseBlockInput> input(new BaseBlockInput(this->getId(), entry->getEntryName()));
    this->inputs[entry->getEntryName()] = input;
}

void ModelBlock::entryRemoved(boost::shared_ptr<IEntryBlock> entry)
{
    this->inputs.erase(entry->getName());
}

void ModelBlock::exitAdded(boost::shared_ptr<IExitBlock> exit)
{
    boost::shared_ptr<BaseBlockOutput> output(new BaseBlockOutput(this->getId(), exit->getExitName()));
    this->outputs[exit->getExitName()] = output;
}

void ModelBlock::exitRemoved(boost::shared_ptr<IExitBlock> exit)
{
    this->outputs.erase(exit->getExitName());
}
