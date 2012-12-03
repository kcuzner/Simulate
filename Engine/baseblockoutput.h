#ifndef BASEBLOCKOUTPUT_H
#define BASEBLOCKOUTPUT_H

#include "interfaces/iblockoutput.h"

class BaseBlockOutput : public IBlockOutput
{
public:
    BaseBlockOutput(IBlock* parent, const std::string& name);

    virtual std::string getName();

    virtual bool isSiblingOf(boost::weak_ptr<IBlockIO> io);

    virtual bool hasParent(IBlock* parent);

    virtual const std::set<boost::weak_ptr<IBlockInput> > &getAttachedInputs();

    virtual bool attachInput(boost::weak_ptr<IBlockInput> input);

    virtual bool detachInput(boost::weak_ptr<IBlockInput> input);

private:
    std::string name;
    IBlock* parentRef; //WARNING: Do not use this to actually reference the block

    std::set<boost::weak_ptr<IBlockInput> > attachedInputs;
};

#endif // BASEBLOCKOUTPUT_H
