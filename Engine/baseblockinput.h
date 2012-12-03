#ifndef BASEBLOCKINPUT_H
#define BASEBLOCKINPUT_H

#include "interfaces/iblockinput.h"

class BaseBlockInput : public IBlockInput
{
public:
    BaseBlockInput(IBlock* parent, const std::string& name);

    virtual std::string getName();

    virtual bool isSiblingOf(boost::weak_ptr<IBlockIO> io);

    virtual bool hasParent(IBlock* parent);

    virtual boost::weak_ptr<IBlockOutput> getAttachedOutput();

    virtual bool attachOutput(boost::weak_ptr<IBlockOutput> output);

    virtual bool detachOutput(boost::weak_ptr<IBlockOutput> output);

private:
    std::string name;
    IBlock* parentRef; //WARNING: Do not use this to actually reference the block

    boost::weak_ptr<IBlockOutput> output;
};

#endif // BASEBLOCKINPUT_H
