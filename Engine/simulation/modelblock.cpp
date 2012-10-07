#include "modelblock.h"

using namespace Simulation;

ModelBlock::ModelBlock(Model *model, Model *executionModel) :
    Block(model)
{
    this->model = executionModel;
}
