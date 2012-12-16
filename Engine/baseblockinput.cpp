#include "baseblockinput.h"

BaseBlockInput::BaseBlockInput(long parentId, const std::string &name)
{
    this->name = name;
    this->blockId = parentId;
}

long BaseBlockInput::getBlockId()
{
    return this->blockId;
}

std::string BaseBlockInput::getName()
{
    return this->name;
}

bool BaseBlockInput::isSiblingOf(boost::weak_ptr<IBlockIO> io)
{
    if (io.expired())
    {
        return false;
    }

    return io.lock()->getBlockId() == this->getBlockId();
}

boost::weak_ptr<IBlockOutput> BaseBlockInput::getAttachedOutput()
{
    return this->output;
}

bool BaseBlockInput::attachOutput(boost::weak_ptr<IBlockOutput> output)
{
    if (!this->output.expired())
        return false; //can't attach while one is still attached

    this->output = output;
    return true;
}

bool BaseBlockInput::detachOutput(boost::weak_ptr<IBlockOutput> output)
{
    if (this->output.lock().get() == output.lock().get())
    {
        this->output = boost::shared_ptr<IBlockOutput>();
        return true;
    }
    return false;
}
