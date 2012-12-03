#ifndef IEXITBLOCK_H
#define IEXITBLOCK_H

#include "iblock.h"

class IExitBlock : IBlock
{
public:
    virtual ~IExitBlock() {}

    virtual std::string getExitName() = 0;
};

#endif // IEXITBLOCK_H
