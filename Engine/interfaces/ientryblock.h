#ifndef IENTRYBLOCK_H
#define IENTRYBLOCK_H

#include <boost/smart_ptr.hpp>
#include "iblock.h"

#define IENTRYBLOCK_OPTION_NAME "Initial Value"

class IEntryBlock : public IBlock
{
public:
    virtual ~IEntryBlock() {}

    virtual void setCurrentValue(IContext* context, boost::shared_ptr<std::vector<double> > value) = 0;

    virtual std::string getEntryName() = 0;
};

#endif // IENTRYBLOCK_H
