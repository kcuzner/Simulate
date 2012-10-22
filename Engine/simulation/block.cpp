#include "block.h"
#include "input.h"
#include "output.h"
#include "blockfactory.h"

using namespace Simulation;

Block::Block(Model *model, QSharedPointer<IBlockCore> core)
    : QObject(model)
{
    this->inputs = QSharedPointer<QHash<QString, QSharedPointer<Input> > >(new QHash<QString, QSharedPointer<Input> >());
    this->outputs = QSharedPointer<QHash<QString, QSharedPointer<Output> > >(new QHash<QString, QSharedPointer<Output> >());

    this->core = core;

    if (core)
    {
        //hook up the signals (runtime errors will result if the block core is implemented without the signals here)
        connect(core->instance(), SIGNAL(addInput(QString,int)), SLOT(coreInputAdded(QString,int)));
        connect(core->instance(), SIGNAL(addOutput(QString,int)), SLOT(coreOutputAdded(QString,int)));
        connect(core->instance(), SIGNAL(removeInput(QString)), SLOT(coreInputRemoved(QString)));
        connect(core->instance(), SIGNAL(removeOutput(QString)), SLOT(coreOutputRemoved(QString)));
    }
    else
    {
        //we will be taking care of some things ourselves
        this->options = QSharedPointer<QHash<QString, double> >(new QHash<QString, double>());
    }
}

Block::~Block()
{
}

QHash<QString, QSharedPointer<Input> > Block::getInputs()
{
    return QHash<QString, QSharedPointer<Input> >((*this->inputs));
}

QHash<QString, QSharedPointer<Output> > Block::getOutputs()
{
    return QHash<QString, QSharedPointer<Output> >((*this->outputs));
}

QStringList Block::getOptionsList()
{
    if (this->core)
        return this->core->getOptionList();
    else
        return QStringList(); //empty list
}

double Block::getOption(const QString &name)
{
    if (this->core)
    {
        //shadow the core
        return this->core->getOption(name);
    }
    else if (this->options)
    {
        //look in our internal option array
        if (this->options->contains(name))
            return (*this->options)[name];
        else
            return 0; //default value
    }
    else
    {
        return 0; //default value
    }
}

void Block::initialize(Context *context)
{
    if (this->core)
    {
        //initialize our core
        this->core->initialize(context->getPersistantBlockContext(this));
    }
}

void Block::execute(Context *context)
{
    if (this->core)
    {
        QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > inputs = context->getBlockInputs(this);
        QSharedPointer<QHash<QString, QSharedPointer<QList<double> > > > outputs = this->core->execute(inputs, context->getPersistantBlockContext(this));

    }
}

void Block::setOption(const QString &name, double value)
{
    if (this->core)
    {
        this->core->setOption(name, value);
    }
    else if (this->options)
    {
        (*this->options)[name] = value;
    }
}

void Block::coreInputAdded(const QString &name, int)
{
    //this is connected to the IBlockCore inputAdded signal
    //we now create a new input with the given name

    this->addInput(name);
}

void Block::coreOutputAdded(const QString &name, int)
{
    //this is connected to the IBlockCore outputAdded signal
    //we now create a new output with the given name

    this->addOutput(name);
}

void Block::coreInputRemoved(const QString &name)
{
    //this is connected to the IBlockCore inputRemoved signal
    //we now remove the input with the given name

    this->removeInput(name);
}

void Block::coreOutputRemoved(const QString &name)
{
    //this is connected to the IBlockCore outputRemoved signal
    //we now remove the output with the given name

    this->removeOutput(name);
}

void Block::setOutputValue(Context* context, const QString &name, QSharedPointer<QList<double> > value)
{
    if (this->outputs->contains(name))
    {
        (*this->outputs)[name]->set(context, value);
    }
}

QSharedPointer<Input> Block::addInput(const QString &name)
{
    if (this->inputs->contains(name))
    {
        //no need to add a new one if they already have one by this name
        return (*this->inputs)[name];
    }

    QSharedPointer<Input> input(new Input(this, name));

    (*this->inputs)[name] = input;

    emit(inputAdded(input));

    return input;
}

QSharedPointer<Output> Block::addOutput(const QString &name)
{
    if (this->outputs->contains(name))
    {
        //no need to add a new output if they already have one by this name
        return (*this->outputs)[name];
    }

    QSharedPointer<Output> output(new Output(this, name));

    (*this->outputs)[name] = output;

    emit(outputAdded(output));

    return output;
}

void Block::removeInput(const QString &name)
{
    if (!this->inputs->contains(name))
    {
        return; //no need for removing something that doesn't exist
    }

    QSharedPointer<Input> input = (*this->inputs)[name];

    this->inputs->remove(name);

    emit(inputRemoved(input));
}

void Block::removeInput(QSharedPointer<Input> input)
{
    if (!this->inputs->contains(input->getName()))
    {
        return;
    }

    this->removeInput(input->getName());
}

void Block::removeOutput(const QString &name)
{
    if (!this->inputs->contains(name))
    {
        return;
    }

    QSharedPointer<Output> output = (*this->outputs)[name];

    this->outputs->remove(name);

    emit(outputRemoved(output));
}

void Block::removeOutput(QSharedPointer<Output> output)
{
    if (!this->outputs->contains(output->getName()))
    {
        return;
    }

    this->removeOutput(output->getName());
}
