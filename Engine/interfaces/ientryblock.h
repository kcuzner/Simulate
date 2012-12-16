#ifndef IENTRYBLOCK_H
#define IENTRYBLOCK_H

#include <boost/smart_ptr.hpp>
#include "iblock.h"

class IEntryBlock : public IBlock
{
public:
    virtual ~IEntryBlock() {}

    virtual void setCurrentValue(IContext* context, boost::shared_ptr<std::vector<double> > value) = 0;

    virtual std::string getEntryName() = 0;
};

#endif // IENTRYBLOCK_H
