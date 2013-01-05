#include "mathgain.h"

#include <sstream>

MathGain::MathGain(long id)
    : BaseBlock(id, "Math", "Gain")
{
    this->addInput("Input");

    this->addOutput("Output");
    this->options.push_back("Gain");
}

boost::shared_ptr<MathGain> MathGain::generate(long id)
{
    return boost::shared_ptr<MathGain>(new MathGain(id));
}

bool MathGain::initialize(IContext *, std::string &error)
{
    if (!this->getOption("Gain"))
    {
        std::stringstream s;
        s << "Not all options specified for Math.Gain " << this->getId();
        error = s.str();
        return false;
    }

    return true;
}

void MathGain::execute(IContext *context, double)
{
    boost::shared_ptr<std::vector<double> > input = context->getInputValue(this->getId(), "Input");

    boost::shared_ptr<std::vector<double> > outputValue(new std::vector<double>());

    double gain = context->getOption(this->getId(), "Gain")->at(0);

    if (input)
    {
        for(std::vector<double>::iterator iter = input->begin(); iter != input->end(); iter++)
        {
            double value = (*iter);
            outputValue->push_back(gain * value);
        }
    }

    context->setOutputValue(this->getId(), "Output", outputValue);
}
