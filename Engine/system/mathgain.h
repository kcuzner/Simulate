#ifndef MATHGAIN_H
#define MATHGAIN_H

#include "../baseblock.h"

namespace System
{
    class MathGain : public BaseBlock
    {
    public:
        MathGain(long id);

        static boost::shared_ptr<MathGain> generate(long id);

        virtual bool initialize(IContext *, std::string&error);

        virtual void execute(IContext *context, double);
    };
}

#endif // MATHGAIN_H
