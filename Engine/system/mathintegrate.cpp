#include "mathintegrate.h"

using namespace System;

MathIntegrate::MathIntegrate(long id)
    : BaseBlock(id, "Math", "Integrate")
{
    this->addInput("Input");

    this->addOutput("Output");
}

boost::shared_ptr<MathIntegrate> MathIntegrate::generate(long id)
{
    return boost::shared_ptr<MathIntegrate>(new MathIntegrate(id));
}

bool MathIntegrate::initialize(IContext *context, std::string &)
{
    boost::shared_ptr<std::vector<double> > value(new std::vector<double>());
    context->setStoredValue(this->getId(), "Value", value);

    return true;
}

void MathIntegrate::execute(IContext *context, double delta)
{

}
