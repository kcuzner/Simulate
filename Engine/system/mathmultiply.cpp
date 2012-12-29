#include "mathmultiply.h"

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

void MathMultiply::initialize(IContext *)
{
}

void MathMultiply::execute(IContext *context, double)
{
    double value = context->getInputValue(this->getId(), "Multiplicand 1")->at(0) * context->getInputValue(this->getId(), "Multiplicand 2")->at(0);

    boost::shared_ptr<std::vector<double> > result(new std::vector<double>());
    result->push_back(value);

    context->setOutputValue(this->getId(), "Product", result);
}
