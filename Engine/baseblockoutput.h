#ifndef BASEBLOCKOUTPUT_H
#define BASEBLOCKOUTPUT_H

#include "interfaces/iblockoutput.h"

class BaseBlockOutput : public IBlockOutput
{
public:
    BaseBlockOutput(long parentId, const std::string& name);

    virtual std::string getName();

    virtual long getBlockId();

    virtual bool isSiblingOf(boost::weak_ptr<IBlockIO> io);

    virtual const std::vector<boost::shared_ptr<IBlockInput> > &getAttachedInputs();

    virtual void detachAllInputs();

    virtual bool attachInput(boost::shared_ptr<IBlockInput> input);

    virtual bool detachInput(boost::shared_ptr<IBlockInput> input);

protected:
    virtual void onInputOutputChanged(IBlockInput* input, IBlockOutput* output);

private:
    std::string name;
    long blockId;

    boost::signals2::connection subscription;
    std::vector<boost::shared_ptr<IBlockInput> > attachedInputs;
};

#endif // BASEBLOCKOUTPUT_H
