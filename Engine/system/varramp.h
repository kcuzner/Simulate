#ifndef VARRAMP_H
#define VARRAMP_H

#include "../baseblock.h"

namespace System
{
    class VarRamp : public BaseBlock
    {
    public:
        VarRamp(long id);

        /**
         * @brief Static generator function for the block factory
         * @param id
         * @return
         */
        static boost::shared_ptr<VarRamp> generate(long id);

        virtual void initialize(IContext *context);

        virtual void execute(IContext *context, double delta);

    protected:
        std::list<std::string> options;
    };
}

#endif // VARRAMP_H
