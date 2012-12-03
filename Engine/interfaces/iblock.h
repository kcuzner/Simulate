#ifndef IBLOCK_H
#define IBLOCK_H

#include <string>
#include <map>
#include <vector>

#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "iblockinput.h"
#include "iblockoutput.h"
#include "icontext.h"

/**
 * @brief Interface to a block
 *
 * Blocks should be supplied with a unique id, a non-unique group name, and a
 * non-unique name when they are constructed
 */
class IBlock
{
public:
    virtual ~IBlock() {}

    virtual int getId() = 0;
    virtual std::string getGroup() = 0;
    virtual std::string getName() = 0;

    /**
     * @brief Returns a block option value
     * @param name Name of the option
     * @return
     */
    virtual const std::vector<double>& getOption(const std::string& name) = 0;
    /**
     * @brief Sets a block option value
     * @param name Name of the option
     * @param value Value of the option
     */
    virtual void setOption(const std::string& name, const std::vector<double>& value) = 0;

    /**
     * @brief Initializes the context to this block
     * @param context Context to initialize
     */
    virtual void initialize(boost::shared_ptr<IContext> context) = 0;

    /**
     * @brief Called to ask the block to execute
     * @param context Context to execute for
     * @param delta Time since the last execute call in seconds
     */
    virtual void execute(boost::shared_ptr<IContext> context, double delta) = 0;

    /**
     * @brief Gets the inputs to this block
     * @return The inputs to this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockInput> >& getInputs() = 0;

    /**
     * @brief Gets the outputs from this blockqa
     * @return The outputs from this block
     */
    virtual const std::map<std::string, boost::shared_ptr<IBlockOutput> >& getOutputs() = 0;

    boost::signals2::signal<void (boost::weak_ptr<IBlockInput>)> sigInputAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlockInput>)> sigInputRemoved;
    boost::signals2::signal<void (boost::weak_ptr<IBlockOutput>)> sigOutputAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlockOutput>)> sigOutputRemoved;
};

#endif // IBLOCK_H
