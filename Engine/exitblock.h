#ifndef EXITBLOCK_H
#define EXITBLOCK_H

#include "interfaces/iexitblock.h"

class ExitBlock : public IExitBlock
{
public:
    ExitBlock(long id, std::string name);

    virtual long getId();

    virtual std::string getGroup();
    virtual std::string getName();

    virtual const std::list<std::string>& getOptionNames();

    virtual boost::shared_ptr<std::vector<double> > getOption(IContext* context, const std::string &name);
    virtual void setOption(IContext*, const std::string &, boost::shared_ptr<std::vector<double> > );

    virtual void initialize(IContext*);

    virtual void execute(IContext *context, double delta);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs();
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs();

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    virtual boost::shared_ptr<std::vector<double> > getCurrentValue(IContext *context);

    virtual std::string getExitName();

protected:
    long id;
    std::string name; //entry name...not block name

    std::list<std::string> options; //there should only end up being no options here

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;

};

#endif // EXITBLOCK_H
