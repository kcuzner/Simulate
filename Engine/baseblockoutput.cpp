#include "baseblockoutput.h"

#include "interfaces/iblockinput.h"

#include <boost/foreach.hpp>
#include <algorithm>

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

const std::vector<boost::shared_ptr<IBlockInput> > &BaseBlockOutput::getAttachedInputs()
{
    return this->attachedInputs;
}

void BaseBlockOutput::detachAllInputs()
{
    BOOST_FOREACH(boost::shared_ptr<IBlockInput> input, this->attachedInputs)
    {
        this->detachInput(input);
    }
}

bool BaseBlockOutput::attachInput(boost::shared_ptr<IBlockInput> input)
{
    if (std::find(this->attachedInputs.begin(), this->attachedInputs.end(), input) != this->attachedInputs.end())
        return false; //it is already attached

    this->attachedInputs.push_back(input);

    //kindly ask the input to switch its owner to us
    if (input->setOutput(this)) //if this returns false, we are already attached somehow
    {
        //subscribe to its events
        this->subscription = input->sigOutputChanged.connect(boost::bind(&BaseBlockOutput::onInputOutputChanged, this, _1, _2));
    }

    this->sigInputAttached(input);

    return true;
}

bool BaseBlockOutput::detachInput(boost::shared_ptr<IBlockInput> input)
{
    std::vector<boost::shared_ptr<IBlockInput> >::iterator iter = std::find(this->attachedInputs.begin(), this->attachedInputs.end(), input);
    if (iter != this->attachedInputs.end())
    {
        //it was found, so disconnect it
        this->attachedInputs.erase(iter);

        //remove our subscription
        if (this->subscription.connected())
            this->subscription.disconnect();

        //ask the input to switch its output to null
        input->setOutput(0);

        return true;
    }

    return false;
}

void BaseBlockOutput::onInputOutputChanged(IBlockInput *input, IBlockOutput *output)
{
    if (output != this)
    {
        //we are no longer connected to this
        //std::vector<boost::shared_ptr<IBlockInput> >::iterator iter = std::find(this->attachedInputs.begin(), this->attachedInputs.end(), input);
        std::vector<boost::shared_ptr<IBlockInput> >::iterator iter;
        for(iter = this->attachedInputs.begin(); iter != this->attachedInputs.end(); iter++)
        {
            if ((*iter).get() == input)
                break;
        }

        if (iter != this->attachedInputs.end())
        {
            //it was found, so disconnect it
            this->attachedInputs.erase(iter);

            //remove our subscription
            if (this->subscription.connected())
                this->subscription.disconnect();
        }
    }
}
