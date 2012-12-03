#ifndef IENTRYBLOCK_H
#define IENTRYBLOCK_H

#include "iblock.h"

class IEntryBlock : public IBlock
{
public:
    virtual ~IEntryBlock() {}

    virtual std::string getEntryName() = 0;
};

#endif // IENTRYBLOCK_H
