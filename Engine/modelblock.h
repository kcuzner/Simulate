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
    ModelBlock(int id, boost::shared_ptr<IModel> model);

    virtual int getId();
    virtual std::string getGroup();
    virtual std::string getName();

    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to get
     * @return Option value
     */
    virtual const std::vector<double>& getOption(const std::string& name);
    /**
     * @brief Options for a ModelBlock are the initial values of the entry/exit pairs that are looped around when a model is executed
     * @param name Name of the option to set
     * @param value Value to set
     */
    virtual void setOption(const std::string& name, const std::vector<double>& value);


    virtual void initialize(boost::shared_ptr<IContext> context);

    virtual void execute(boost::shared_ptr<IContext> context, double delta);

    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs();

    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs();

    virtual boost::shared_ptr<IModel> getModel();

protected:
    void entryAdded(boost::shared_ptr<IEntryBlock>);
    void entryRemoved(boost::shared_ptr<IEntryBlock>);
    void exitAdded(boost::shared_ptr<IExitBlock>);
    void exitRemoved(boost::shared_ptr<IExitBlock>);

private:
    int id;
    boost::shared_ptr<IModel> model;
    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;
};

#endif // MODELBLOCK_H
