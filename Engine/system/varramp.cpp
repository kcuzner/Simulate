#include "varramp.h"

#include <sstream>

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

bool VarRamp::initialize(IContext *context, std::string& error)
{
    if (!this->getOption("Positive Slope") ||
            !this->getOption("Negative Slope") ||
            !this->getOption("Low Value") ||
            !this->getOption("High Value") ||
            !this->getOption("Starting Value"))
    {
        std::stringstream s;
        s << "Not all options specified for Var.Ramp " << this->getId();
        error = s.str();
        return false;
    }

    context->setStoredValue(this->getId(), "Value", this->getOption("Starting Value"));
    return true;
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

    if (current <= context->getOption(this->getId(), "Low Value")->at(0))
    {
        //high slope time
        current += context->getOption(this->getId(), "Positive Slope")->at(0) * delta;
    }
    else if (current >= context->getOption(this->getId(), "High Value")->at(0))
    {
        //low slope time
        current -= context->getOption(this->getId(), "Negative Slope")->at(0) * delta;
    }

    (*value)[0] = current;

}
