#ifndef ISIMULATIONCORE_H
#define ISIMULATIONCORE_H

#include <string>

#include "interfaces/iengine.h"
#include "interfaces/iblockcollection.h"
#include "interfaces/iblockfactory.h"
#include "interfaces/ifileloader.h"

#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>

/**
 * @brief Interface to the main simulation core. This class is implemented
 * in the SimulationCore class and shouldn't have to be re-implmented. This
 * definition only exists so that things such as the IFileLoader can be
 * passed a reference to an ISimulationCore to use when loading the files.
 */
class ISimulationCore
{
public:
    virtual ~ISimulationCore() {}

    /**
     * @brief Adds an engine generator with the given name to the simulation core
     * @param name
     * @param generator
     * @return False if an engine with that name has already been added
     */
    virtual bool addEngineType(const std::string& name, boost::function<boost::shared_ptr<IEngine> (boost::shared_ptr<IModel>, int, double)> generator) = 0;

    virtual boost::shared_ptr<IEngine> createEngine(boost::shared_ptr<IModel> model, int steps, double delta) = 0;
    virtual boost::shared_ptr<IEngine> createEngine(const std::string& engineTypeName, boost::shared_ptr<IModel> model, int steps, double delta) = 0;

    virtual void setEngineType(const std::string& typeName) = 0;

    /**
     * @brief Adds a model generator to this simulation core
     * @param generator
     * @return
     */
    virtual bool addModelType(boost::shared_ptr<IModelGenerator> generator) = 0;

    virtual boost::shared_ptr<IModel> createModel(const std::string& name) = 0;
    virtual boost::shared_ptr<IModel> createModel(const std::string& modelTypeName, const std::string& name) = 0;

    virtual void setModelType(const std::string& modelTypeName) = 0;

    /**
     * @brief Adds a block collection to the simulation core and adds it to the block factory
     * @param name
     * @param generator
     * @return
     */
    virtual bool addBlockCollection(boost::shared_ptr<IBlockCollection> collection) = 0;

    /**
     * @brief Adds a file loader to this simulation.
     * @param loader
     * @return False if a loader for the exact file pattern exists
     */
    virtual bool addFileLoader(boost::shared_ptr<IFileLoader> loader) = 0;

    /**
     * @brief Loads a simulation from a file using one of the file loaders attached to the simulation core
     * @param fileName
     * @return NULL if failed
     */
    virtual boost::shared_ptr<ISimulation> loadSimulation(const std::string& fileName) = 0;

    /**
     * @brief Saves a simulation to a file using one of the file loaders attached to the simulation core
     * @param simulation
     * @param fileName
     * @return False if failed
     */
    virtual bool saveSimulation(boost::shared_ptr<ISimulation> simulation, const std::string& fileName) = 0;

    /**
     * @brief Returns a message about the last error that occured when saving or loading a file
     * @return
     */
    virtual const std::string& getLastFileError() = 0;

    /**
     * @brief Creates a new empty simulation object with no models attached yet
     * @param steps
     * @param delta
     * @return
     */
    virtual boost::shared_ptr<ISimulation> createSimulation(int steps, double delta) = 0;
};

#endif // ISIMULATIONCORE_H
