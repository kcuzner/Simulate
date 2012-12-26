#include "varramp.h"

using namespace System;


VarRamp::VarRamp(long id)
    : BaseBlock(id, "Var", "Ramp")
{
    this->options.push_back("Positive Slope");
    this->options.push_back("Negative Slope");
    this->options.push_back("Low Value");
    this->options.push_back("High Value");
    this->options.push_back("Starting Value");
}

boost::shared_ptr<VarRamp> VarRamp::generate(long id)
{
    return boost::shared_ptr<VarRamp>(new VarRamp(id));
}

void VarRamp::initialize(IContext *context)
{
    context->setStoredValue(this->getId(), "Value", context->getStoredValue(this->getId(), "Starting Value"));
}

void VarRamp::execute(IContext *context, double delta)
{
    //since this is a pointer, all we are going to do is modify the pointed to value
    //no need to store it again after this
    boost::shared_ptr<std::vector<double> > value = context->getStoredValue(this->getId(), "Value");

    if (!value)
    {
        //value needs to be set to a new vector
        value = boost::shared_ptr<std::vector<double> >(new std::vector<double>());
    }

    if (!value->size())
    {
        //value needs to have its first value initialized
        value->push_back(0.0);
    }

    double current = value->at(0);

    if (current <= context->getStoredValue(this->getId(), "Low Value")->at(0))
    {
        //high slope time
        current += context->getStoredValue(this->getId(), "Positive Slope")->at(0) * delta;
    }
    else if (current >= context->getStoredValue(this->getId(), "High Value")->at(0))
    {
        //low slope time
        current -= context->getStoredValue(this->getId(), "Negative Slope")->at(0) * delta;
    }

    (*value)[0] = current;

}
