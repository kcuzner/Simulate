#include "baseblockoutput.h"

BaseBlockOutput::BaseBlockOutput(long parentId, const std::string &name)
{
    this->name = name;
    this->blockId = parentId;
}

std::string BaseBlockOutput::getName()
{
    return this->name;
}

long BaseBlockOutput::getBlockId()
{
    return this->blockId;
}

bool BaseBlockOutput::isSiblingOf(boost::weak_ptr<IBlockIO> io)
{
    if (io.expired())
    {
        return false;
    }

    return io.lock()->getBlockId() == this->getBlockId();
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
