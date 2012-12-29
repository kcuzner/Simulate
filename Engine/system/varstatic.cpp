#include "varstatic.h"

#include <iostream>

using namespace System;

VarStatic::VarStatic(long id)
    : BaseBlock(id, "Var", "Static")
{
    this->options.push_back("Value");

    this->addOutput("Output");
}

boost::shared_ptr<VarStatic> VarStatic::generate(long id)
{
    return boost::shared_ptr<VarStatic>(new VarStatic(id));
}

void VarStatic::initialize(IContext *)
{
}

void VarStatic::execute(IContext *context, double)
{
    context->setOutputValue(this->getId(), "Output", context->getStoredValue(this->getId(), "Value"));
}
