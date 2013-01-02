#ifndef IFILEMODELDESCRIPTION_H
#define IFILEMODELDESCRIPTION_H

#include <string>
#include <map>

#include "ifileblockdescription.h"

/**
 * @brief Interface returned by an IFileLoader describing a model
 */
class IFileModelDescription
{
public:
    virtual ~IFileModelDescription() {}

    virtual const std::map<std::string, std::string>& getEntryNames() = 0;
    virtual const std::map<std::string, std::string>& getExitNames() = 0;

    virtual const std::map<int, IFileBlockDescription>& getBlocks() = 0;

    /**
     * @brief Models may place any data here that would be useful in loading them
     * @return
     */
    virtual const std::map<std::string, boost::any>& getExtendedDescription() = 0;

    virtual void setExtendedDescriptionValue(std::string name, const boost::any& value) = 0;
};

#endif // IFILEMODELDESCRIPTION_H
