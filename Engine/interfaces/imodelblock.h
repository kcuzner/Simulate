#ifndef IMODELBLOCK_H
#define IMODELBLOCK_H

#include "iblock.h"
#include "imodel.h"

/**
 * @brief Interface to a block that encapsulates a model
 */
class IModelBlock : public IBlock
{
public:
    virtual ~IModelBlock() {}

    virtual boost::shared_ptr<IModel> getModel() = 0;
};

#endif // IMODELBLOCK_H
