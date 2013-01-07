#ifndef MODELBLOCK_H
#define MODELBLOCK_H

#include "interfaces/imodel.h"
#include "interfaces/imodelblock.h"

/**
 * @brief A block which is attached to a model and executes it as a sub-block
 * This block is created in group engine with type model
 */
class ModelBlock : public IModelBlock
{
public:
    ModelBlock(long id, boost::shared_ptr<IModel> model);

    virtual long getId() const;

    virtual std::string getGroup() const;
    virtual std::string getName() const;

    virtual const std::list<std::string>& getOptionNames() const;

    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to get
     * @return Option value
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(const std::string&) const;
    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to set
     * @param value Value to set
     */
    virtual void setOption(const std::string&, boost::shared_ptr<std::vector<double> >);

    virtual const std::map<std::string, boost::shared_ptr<std::vector<double> > >& getOptions() const;


    virtual bool initialize(IContext* context, std::string&);

    virtual void execute(IContext* context, double);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs() const;

    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs() const;

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    virtual const std::map<std::string, std::string>& getData() const;
    virtual const std::string& getData(const std::string& key) const;
    virtual void setData(const std::string& key, const std::string& value);

    virtual boost::shared_ptr<IModel> getModel() const;

    virtual boost::shared_ptr<IContext> getContext(IContext* context) const;

protected:
    void entryAdded(IModel*, boost::shared_ptr<IEntryBlock>);
    void entryRemoved(IModel*, boost::shared_ptr<IEntryBlock>);
    void exitAdded(IModel*, boost::shared_ptr<IExitBlock>);
    void exitRemoved(IModel*, boost::shared_ptr<IExitBlock>);

private:
    long id;
    boost::shared_ptr<IModel> model;

    std::map<std::string, std::string> data;

    std::map<std::string, boost::shared_ptr<std::vector<double> > > optionValues;

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;
    std::map<std::string, boost::shared_ptr<IEntryBlock> > inputEntryBlocks;
    std::map<std::string, boost::shared_ptr<IExitBlock> > outputExitBlocks;

    std::map<std::string, std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > > optionBlocks;
    std::list<std::string> optionBlockNames;
};

#endif // MODELBLOCK_H
