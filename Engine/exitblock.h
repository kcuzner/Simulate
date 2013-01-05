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

    virtual boost::shared_ptr<std::vector<double> > getOption(const std::string &) const;
    virtual void setOption(const std::string &, boost::shared_ptr<std::vector<double> > );
    virtual const std::map<std::string, boost::shared_ptr<std::vector<double> > >& getOptions() const;

    virtual bool initialize(IContext*, std::string&);

    virtual void execute(IContext *context, double delta);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs();
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs();

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    virtual const std::map<std::string, std::string>& getData();
    virtual const std::string& getData(const std::string& key);
    virtual void setData(const std::string& key, const std::string& value);

    virtual boost::shared_ptr<std::vector<double> > getCurrentValue(IContext *context);

    virtual std::string getExitName();

protected:
    long id;
    std::string name; //entry name...not block name

    std::map<std::string, std::string> data;

    std::list<std::string> options; //there should only end up being no options here
    std::map<std::string, boost::shared_ptr<std::vector<double> > > optionValues;

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;

};

#endif // EXITBLOCK_H
