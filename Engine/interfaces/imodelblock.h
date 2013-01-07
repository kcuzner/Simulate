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

    virtual boost::shared_ptr<IModel> getModel() const = 0;

    /**
     * @brief Returns the child context for this modelblock in the passed context
     * @param context ModelBlock context
     * @return Child Context for the passed Parent Context
     */
    virtual boost::shared_ptr<IContext> getContext(IContext* context) const = 0;
};

#endif // IMODELBLOCK_H
