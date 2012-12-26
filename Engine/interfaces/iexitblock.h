#ifndef IEXITBLOCK_H
#define IEXITBLOCK_H

#include "iblock.h"

#define IEXITBLOCK_INPUT_NAME "Input"

class IExitBlock : public IBlock
{
public:
    virtual ~IExitBlock() {}

    virtual boost::shared_ptr<std::vector<double> > getCurrentValue(IContext* context) = 0;

    virtual std::string getExitName() = 0;
};

#endif // IEXITBLOCK_H
