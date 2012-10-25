#include "modelblock.h"

using namespace Simulation;
using namespace Interfaces;

ModelBlock::ModelBlock(Model *model, QSharedPointer<Model> executionModel) :
    Block(model, QSharedPointer<IBlockCore>())
{
    this->model = executionModel;
}

QStringList ModelBlock::getOptionsList()
{
    return QStringList();
}

void ModelBlock::execute(Context *context)
{
}


void ModelBlock::modelEntryAdded(QSharedPointer<EntryBlock> entry)
{
}

void ModelBlock::modelExitAdded(QSharedPointer<ExitBlock> exit)
{
}

void ModelBlock::modelEntryRemoved(QSharedPointer<EntryBlock> entry)
{
}

void ModelBlock::modelExitRemoved(QSharedPointer<ExitBlock> exit)
{
}
