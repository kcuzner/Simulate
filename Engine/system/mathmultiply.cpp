#include "mathmultiply.h"

#include <sstream>

using namespace System;

MathMultiply::MathMultiply(long id)
    : BaseBlock(id, "Math", "Multiply")
{
    this->addInput("Multiplicand 1");
    this->addInput("Multiplicand 2");

    this->addOutput("Product");
}

boost::shared_ptr<MathMultiply> MathMultiply::generate(long id)
{
    return boost::shared_ptr<MathMultiply>(new MathMultiply(id));
}

bool MathMultiply::initialize(IContext *, std::string &)
{
    return true;
}

void MathMultiply::execute(IContext *context, double)
{
    boost::shared_ptr<std::vector<double> > multiplicand1 = context->getInputValue(this->getId(), "Multiplicand 1");
    boost::shared_ptr<std::vector<double> > multiplicand2 = context->getInputValue(this->getId(), "Multiplicand 2");
    if (multiplicand1 && multiplicand2)
    {
        //only if we find non-null values for both do we set the product
        double value = context->getInputValue(this->getId(), "Multiplicand 1")->at(0) * context->getInputValue(this->getId(), "Multiplicand 2")->at(0);

        boost::shared_ptr<std::vector<double> > result(new std::vector<double>());
        result->push_back(value);

        context->setOutputValue(this->getId(), "Product", result);
    }
}
