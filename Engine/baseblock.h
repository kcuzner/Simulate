#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "interfaces/iblock.h"

/**
 * @brief BaseBlock which implements certain functions common for blocks in the
 * engine
 */
class BaseBlock : public IBlock
{
public:
    BaseBlock(long id, const std::string& group, const std::string& name);

    virtual long getId();
    virtual std::string getGroup();
    virtual std::string getName();

    /**
     * @brief This implementation returns the options named in the option list
     * @return
     */
    virtual const std::list<std::string>& getOptionNames();

    /**
     * @brief This implementation retrieves options directly with the names being stored values and checking against the list
     * @param context
     * @param name
     * @return
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(IContext *context, const std::string &name);

    /**
     * @brief This implementation stores options directly with the names being stored values checked against the list
     * @param context
     * @param name
     * @param value
     */
    virtual void setOption(IContext *context, const std::string &name, boost::shared_ptr<std::vector<double> > value);

    /**
     * @brief Gets the inputs to this block
     * @return The inputs to this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs();

    /**
     * @brief Gets the outputs from this blockqa
     * @return The outputs from this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs();

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    boost::signals2::signal<void (boost::weak_ptr<IBlockInput>)> sigInputAdded;
    boost::signals2::signal<void (boost::weak_ptr<IBlockInput>)> sigInputRemoved;
    boost::signals2::signal<void (boost::weak_ptr<IBlockOutput>)> sigOutputAdded;
    boost::signals2::signal<void (boost::weak_ptr<IBlockOutput>)> sigOutputRemoved;

protected:
    boost::shared_ptr<IBlockInput> addInput(const std::string& name);
    void removeInput(const std::string& name);
    boost::shared_ptr<IBlockOutput> addOutput(const std::string& name);
    void removeOutput(const std::string& name);

    std::list<std::string> options;

private:
    long id;
    std::string name, group;

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;
};

#endif // BASEBLOCK_H
