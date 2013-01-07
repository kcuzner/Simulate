#ifndef ENTRYBLOCK_H
#define ENTRYBLOCK_H

#include "interfaces/ientryblock.h"

class EntryBlock : public IEntryBlock
{
public:
    EntryBlock(long id, std::string name);

    virtual long getId() const;

    virtual std::string getGroup() const;
    virtual std::string getName() const;

    virtual const std::list<std::string>& getOptionNames() const;

    virtual boost::shared_ptr<std::vector<double> > getOption(const std::string &name) const;
    virtual void setOption(const std::string &name, boost::shared_ptr<std::vector<double> > value);

    virtual const std::map<std::string, boost::shared_ptr<std::vector<double> > >& getOptions() const;

    virtual bool initialize(IContext*, std::string &error);

    virtual void execute(IContext *context, double delta);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs() const;
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs() const;

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    virtual const std::map<std::string, std::string>& getData() const;
    virtual const std::string& getData(const std::string& key) const;
    virtual void setData(const std::string& key, const std::string& value);

    virtual void setCurrentValue(IContext *context, boost::shared_ptr<std::vector<double> > value);

    virtual const std::string& getEntryName() const;

protected:
    long id;
    std::string name; //entry name...not block name

    std::map<std::string, std::string> data;

    std::list<std::string> options; //there should only end up being one option here...the initial value

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;

    std::map<std::string, boost::shared_ptr<std::vector<double> > > optionValues;
};

#endif // ENTRYBLOCK_H
