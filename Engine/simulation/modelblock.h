#ifndef MODELBLOCK_H
#define MODELBLOCK_H

#include "block.h"

namespace Simulation
{
    /**
     * @brief Block which holds and executes a block in a child context
     */
    class ModelBlock : Block
    {
    public:
        ModelBlock(Model* model, Model* executionModel);

    protected:
        Model* model;
    };

}

#endif // MODELBLOCK_H
