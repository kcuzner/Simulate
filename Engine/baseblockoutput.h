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

    virtual const std::set<boost::weak_ptr<IBlockInput> > &getAttachedInputs();

    virtual bool attachInput(boost::weak_ptr<IBlockInput> input);

    virtual bool detachInput(boost::weak_ptr<IBlockInput> input);

private:
    std::string name;
    long blockId;

    std::set<boost::weak_ptr<IBlockInput> > attachedInputs;
};

#endif // BASEBLOCKOUTPUT_H
