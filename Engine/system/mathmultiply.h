#ifndef MATHMULTIPLY_H
#define MATHMULTIPLY_H

#include "../baseblock.h"

namespace System
{
    class MathMultiply : public BaseBlock
    {
    public:
        MathMultiply(long id);

        static boost::shared_ptr<MathMultiply> generate(long id);

        virtual bool initialize(IContext *, std::string&);

        virtual void execute(IContext *context, double);
    };
}

#endif // MATHMULTIPLY_H
