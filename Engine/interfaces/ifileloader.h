#ifndef IFILELOADER_H
#define IFILELOADER_H

#include <exception>
#include <string>

#include <boost/smart_ptr.hpp>

#include "isimulation.h"

class ISimulationCore; //forward declaration of ISimulationCore

/**
 * @brief Interface for a file loading class.
 * File saving/loading is accomplished by recursively
 * scanning all the IFile* descriptions returned from
 * models and blocks, starting at the root model. It
 * is up to the individual implementation of the file
 * loader to decide how files will be stored.
 *
 * NOTE: Blocks and Models should take in their respective
 * description classes as constructor arguments
 */
class IFileLoader
{
public:
    virtual ~IFileLoader() {}

    /**
     * @brief Returns a Regex pattern which will match all filenames this loader can process
     * @return
     */
    virtual std::string getFileMatchPattern() = 0;

    /**
     * @brief Returns the human readable description of this file type
     * @return
     */
    virtual std::string getFileTypeName() = 0;

    /**
     * @brief Loads a file with the given name.
     * @param fileName
     * @return NULL if unable to load the file
     */
    virtual boost::shared_ptr<ISimulation> loadFile(ISimulationCore* core, std::string fileName) = 0;

    /**
     * @brief Saves a file with the given name
     * @param model
     * @param fileName
     * @return true if successful
     */
    virtual bool saveFile(ISimulationCore* core, boost::shared_ptr<ISimulation> simulation, std::string fileName) = 0;

    /**
     * @brief Returns a string describing the last error that occured when saving or loading a file
     * @return
     */
    virtual const std::string& getLastError() const = 0;
};

#endif // IFILELOADER_H
