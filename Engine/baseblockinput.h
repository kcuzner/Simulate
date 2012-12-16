#ifndef BASEBLOCKINPUT_H
#define BASEBLOCKINPUT_H

#include "interfaces/iblockinput.h"

class BaseBlockInput : public IBlockInput
{
public:
    BaseBlockInput(long parentId, const std::string& name);

    virtual long getBlockId();

    virtual std::string getName();

    virtual bool isSiblingOf(boost::weak_ptr<IBlockIO> io);

    virtual boost::weak_ptr<IBlockOutput> getAttachedOutput();

    virtual bool attachOutput(boost::weak_ptr<IBlockOutput> output);

    virtual bool detachOutput(boost::weak_ptr<IBlockOutput> output);
private:
    std::string name;
    long blockId; //parent block id

    boost::weak_ptr<IBlockOutput> output;
};

#endif // BASEBLOCKINPUT_H
