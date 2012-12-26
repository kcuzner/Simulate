#include "baseblockinput.h"

BaseBlockInput::BaseBlockInput(long parentId, const std::string &name)
{
    this->name = name;
    this->blockId = parentId;

    this->output = 0;
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

bool BaseBlockInput::isAttached()
{
    return output != 0;
}

bool BaseBlockInput::setOutput(IBlockOutput *output)
{
    if (this->output != output)
    {
        //we are changing owners
        this->output = output;
        this->sigOutputChanged(this, output);

        return true;
    }

    return false;
}
