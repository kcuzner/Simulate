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

    virtual bool isAttached();

    virtual bool setOutput(IBlockOutput* output);
private:
    std::string name;
    long blockId; //parent block id

    IBlockOutput* output; //don't use this for anything but comparisons on when to send the changed signal
};

#endif // BASEBLOCKINPUT_H
