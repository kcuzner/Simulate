#ifndef IFILEBLOCKDESCRIPTION_H
#define IFILEBLOCKDESCRIPTION_H

#include <string>
#include <map>
#include <vector>
#include <utility>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

/**
 * @brief Describes a block and all information that should be necessary to construct it.
 * Non-context dependent information is stored here.
 */
class IFileBlockDescription
{
public:
    virtual ~IFileBlockDescription() {}

    virtual int getId() = 0;
    virtual const std::string& getGroup() = 0;
    virtual const std::string& getName() = 0;

    /**
     * @brief Blocks may place any data here that would be useful in loading them
     * such as entry/exit descriptions, modelblock descriptions, visual descriptions,
     * etc
     * @return
     */
    virtual const std::map<std::string, boost::any>& getExtendedDescription() = 0;

    virtual void setExtendedDescriptionValue(std::string name, const boost::any& value) = 0;

    /**
     * @brief Returns the connections to this block sorted by output name.
     * @return map of <output name, std::pair<block id, input name> >
     */
    virtual const std::map<std::string, std::pair<int, std::string> >& getConnections();
};

#endif // IFILEBLOCKDESCRIPTION_H
