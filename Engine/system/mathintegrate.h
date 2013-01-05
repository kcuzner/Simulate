#ifndef MATHINTEGRATE_H
#define MATHINTEGRATE_H

#include "../baseblock.h"

class MathIntegrate : public BaseBlock
{
public:
    MathIntegrate(long id);

    static boost::shared_ptr<MathIntegrate> generate(long id);

    virtual bool initialize(IContext *context, std::string&);

    virtual void execute(IContext *context, double delta);
};

#endif // MATHINTEGRATE_H
