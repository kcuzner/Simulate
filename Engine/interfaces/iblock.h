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

#include "ifileblockdescription.h"

/**
 * Special Options. These are meant for internal use and are prefixed with
 * an underscore so they are omitted from general option listings
 */

//if this option is set to anything but null, this is a visual block
#define BLOCK_OPTION_VISUAL "_VISUAL_ENABLED"
#define BLOCK_OPTION_VISUAL_CHANNELS "_VISUAL_CHANNELS"
#define BLOCK_OPTION_VISUAL_DATA_PREFIX "_VISUAL_DATA"

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

    /**
     * @brief Returns the model-unique idenfier for this block
     * @return
     */
    virtual long getId() = 0;
    /**
     * @brief Returns the group this block belongs to
     * @return
     */
    virtual std::string getGroup() = 0;
    /**
     * @brief Returns the name of this block type
     * @return
     */
    virtual std::string getName() = 0;

    /**
     * @brief Returns block option names
     * @return
     */
    virtual const std::list<std::string>& getOptionNames() = 0;

    /**
     * @brief Returns a block option value
     * @param name Name of the option
     * @return
     */
    virtual boost::shared_ptr<std::vector<double> > getOption(IContext* context, const std::string& name) = 0;
    /**
     * @brief Sets a block option value
     * @param name Name of the option
     * @param value Value of the option
     */
    virtual void setOption(IContext* context, const std::string& name, boost::shared_ptr<std::vector<double> > value) = 0;

    /**
     * @brief Initializes the context to this block. This will be called each time the context is reset the first step.
     * @param context Context to initialize
     */
    virtual void initialize(IContext* context) = 0;

    /**
     * @brief Called to ask the block to execute
     * @param context Guaranteed safe pointer to the context to execute for
     * @param delta Time since the last execute call in seconds
     */
    virtual void execute(IContext* context, double delta) = 0;

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

    /**
     * @brief Connects an output from this block to the input of the passed block
     * @param output This block's output name to connect from
     * @param block Block to connect to
     * @param input Input on the other block to connect to
     * @param overwrite If true, this will disconnect outputs connected to the input
     * @return False if something was already connected and we are not overwriting
     */
    virtual bool connect(const std::string& output, boost::shared_ptr<IBlock> block, const std::string& input, bool overwrite) = 0;

    /**
     * @brief Returns all the arbitrary data associated with this block
     * @return
     */
    virtual const std::map<std::string, std::string>& getData() = 0;
    /**
     * @brief Returns a specific arbitrary value. If it doesn't exist, an out of range exception should bubble up
     * @param key
     * @return
     */
    virtual const std::string& getData(const std::string& key) = 0;
    /**
     * @brief Sets an arbitrary data value
     * @param key
     * @param value
     */
    virtual void setData(const std::string& key, const std::string& value) = 0;

    boost::signals2::signal<void (boost::weak_ptr<IBlockInput>)> sigInputAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlockInput>)> sigInputRemoved;
    boost::signals2::signal<void (boost::weak_ptr<IBlockOutput>)> sigOutputAdded;
    boost::signals2::signal<void (boost::shared_ptr<IBlockOutput>)> sigOutputRemoved;
};

#endif // IBLOCK_H
