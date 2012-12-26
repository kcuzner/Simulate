#ifndef VARSTATIC_H
#define VARSTATIC_H

#include "../baseblock.h"

namespace System
{
    /**
     * @brief Static variable block
     */
    class VarStatic : public BaseBlock
    {
    public:
        VarStatic(long id);

        /**
         * @brief Static generator function for the block factory
         * @param id
         * @return
         */
        static boost::shared_ptr<VarStatic> generate(long id);

        virtual void initialize(IContext *);

        virtual void execute(IContext *context, double);
    };
}

#endif // VARSTATIC_H
