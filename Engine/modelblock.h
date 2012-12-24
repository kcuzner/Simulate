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

    virtual long getId();

    virtual std::string getGroup();
    virtual std::string getName();

    virtual const std::list<std::string>& getOptionNames();

    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to get
     * @return Option value
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(IContext* context, const std::string& name);
    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to set
     * @param value Value to set
     */
    virtual void setOption(IContext* context, const std::string& name, boost::shared_ptr<std::vector<double> > value);


    virtual void initialize(IContext* context);

    virtual void execute(IContext* context, double delta);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs();

    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs();

    virtual boost::shared_ptr<IModel> getModel();

    virtual boost::shared_ptr<IContext> getContext(IContext* context);

protected:
    void entryAdded(boost::shared_ptr<IEntryBlock>);
    void entryRemoved(boost::shared_ptr<IEntryBlock>);
    void exitAdded(boost::shared_ptr<IExitBlock>);
    void exitRemoved(boost::shared_ptr<IExitBlock>);

private:
    long id;
    boost::shared_ptr<IModel> model;

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;
    std::map<std::string, boost::shared_ptr<IEntryBlock> > inputEntryBlocks;
    std::map<std::string, boost::shared_ptr<IExitBlock> > outputExitBlocks;

    std::map<std::string, std::pair<boost::shared_ptr<IEntryBlock>, boost::shared_ptr<IExitBlock> > > optionBlocks;
    std::list<std::string> optionBlockNames;
};

#endif // MODELBLOCK_H
