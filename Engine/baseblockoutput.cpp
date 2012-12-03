#include "baseblockoutput.h"

BaseBlockOutput::BaseBlockOutput(IBlock *parent, const std::string &name)
{
    this->name = name;
    this->parentRef = parent;
}

std::string BaseBlockOutput::getName()
{
    return this->name;
}

bool BaseBlockOutput::isSiblingOf(boost::weak_ptr<IBlockIO> io)
{
    if (io.expired())
    {
        return false;
    }

    return io.lock()->hasParent(this->parentRef);
}

bool BaseBlockOutput::hasParent(IBlock *parent)
{
    return this->parentRef == parent;
}

const std::set<boost::weak_ptr<IBlockInput> > &BaseBlockOutput::getAttachedInputs()
{
    return this->attachedInputs;
}

bool BaseBlockOutput::attachInput(boost::weak_ptr<IBlockInput> input)
{
    if (input.expired())
        return false;

    this->attachedInputs.insert(input);

    return true;
}

bool BaseBlockOutput::detachInput(boost::weak_ptr<IBlockInput> input)
{
    if (input.expired())
        return false;

    this->attachedInputs.erase(input);

    return true;
}
