#include "varstatic.h"

#include <iostream>
#include <sstream>

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

bool VarStatic::initialize(IContext *, std::string& error)
{
    if (!this->getOption("Value"))
    {
        std::stringstream s;
        s << "Not all options specified for Var.Static " << this->getId();
        error = s.str();
        return false;
    }

    return true;
}

void VarStatic::execute(IContext *context, double)
{
    context->setOutputValue(this->getId(), "Output", context->getOption(this->getId(), "Value"));
}
