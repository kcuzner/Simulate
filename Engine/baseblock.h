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

    virtual long getId() const;
    virtual std::string getGroup() const;
    virtual std::string getName() const;

    /**
     * @brief This implementation returns the options named in the option list
     * @return
     */
    virtual const std::list<std::string>& getOptionNames() const;

    /**
     * @brief This implementation retrieves options directly with the names being stored values and checking against the list
     * THIS SHOULD NOT BE USED DURING execute()!!! IContext::getOption should be used instead. This prevents thread safety
     * issues by delegating that responsibility to the context
     * @param context
     * @param name
     * @return
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(const std::string &name) const;

    /**
     * @brief This implementation stores options directly with the names being stored values checked against the list
     * @param context
     * @param name
     * @param value
     */
    virtual void setOption(const std::string &name, boost::shared_ptr<std::vector<double> > value);

    /**
     * @brief Returns all the options for this block
     * @return
     */
    virtual const std::map<std::string, boost::shared_ptr<std::vector<double> > >& getOptions() const;

    /**
     * @brief Gets the inputs to this block
     * @return The inputs to this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs() const;

    /**
     * @brief Gets the outputs from this blockqa
     * @return The outputs from this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs() const;

    virtual bool connect(const std::string &outputName, boost::shared_ptr<IBlock> block, const std::string &inputName, bool overwrite);

    virtual const std::map<std::string, std::string>& getData() const;
    virtual const std::string& getData(const std::string& key) const;
    virtual void setData(const std::string& key, const std::string& value);

protected:
    boost::shared_ptr<IBlockInput> addInput(const std::string& name);
    void removeInput(const std::string& name);
    boost::shared_ptr<IBlockOutput> addOutput(const std::string& name);
    void removeOutput(const std::string& name);

    std::list<std::string> options;

private:
    long id;
    std::string name, group;

    std::map<std::string, std::string> data;

    std::map<std::string, boost::shared_ptr<std::vector<double> > > optionValues;

    std::map<std::string, boost::shared_ptr<IBlockInput> > inputs;
    std::map<std::string, boost::shared_ptr<IBlockOutput> > outputs;
};

#endif // BASEBLOCK_H
