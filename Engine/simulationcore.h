#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include "interfaces/isimulationcore.h"

/**
 * @brief Top level class used in the engine to track engine types, factories,
 * file loaders, and all other things. While the engine can be used without
 * this, this class is designed to allow different implementations of the
 * engine interfaces to work together.
 */
class SimulationCore : public ISimulationCore
{
public:
    static boost::shared_ptr<ISimulationCore> getInstance();

    /**
     * @brief Adds an engine generator with the given name to the simulation core
     * @param name
     * @param generator
     * @return False if an engine with that name has already been added
     */
    virtual bool addEngineType(const std::string& name, boost::function<boost::shared_ptr<IEngine> (boost::shared_ptr<IModel>, int, double)> generator);

    virtual boost::shared_ptr<IEngine> createEngine(const std::string& name, boost::shared_ptr<IModel> model, int steps, double delta);
    virtual boost::shared_ptr<IEngine> createEngine(boost::shared_ptr<IModel> model, int steps, double delta);
    virtual boost::shared_ptr<IEngine> createEngine(boost::shared_ptr<ISimulation> simulation);

    virtual void setEngineType(const std::string &typeName);

    virtual bool addModelType(boost::shared_ptr<IModelGenerator> generator);

    virtual boost::shared_ptr<IModel> createModel(const std::string& modelTypeName, const std::string& modelName);
    virtual boost::shared_ptr<IModel> createModel(const std::string& name);

    virtual void setModelType(const std::string &modelTypeName);

    /**
     * @brief Adds a block collection to the simulation core and adds it to all the attached block factories
     * @param name
     * @param generator
     * @return
     */
    virtual bool addBlockCollection(boost::shared_ptr<IBlockCollection> collection);

    virtual bool addFileLoader(boost::shared_ptr<IFileLoader> loader);

    /**
     * @brief Loads a simulation from a file using one of the file loaders attached to the simulation core
     * @param fileName
     * @return NULL if failed
     */
    virtual boost::shared_ptr<ISimulation> loadSimulation(const std::string& fileName);

    /**
     * @brief Saves a simulation to a file using one of the file loaders attached to the simulation core
     * @param simulation
     * @param fileName
     * @return False if failed
     */
    virtual bool saveSimulation(boost::shared_ptr<ISimulation> simulation, const std::string& fileName);

    /**
     * @brief Returns a message about the last error that occured when saving or loading a file
     * @return
     */
    virtual const std::string& getLastFileError();

    virtual boost::shared_ptr<ISimulation> createSimulation(int steps, double delta);
    virtual boost::shared_ptr<ISimulation> createSimulation(int steps, double delta, const std::string& fileName);

private:
    SimulationCore();

    static boost::shared_ptr<SimulationCore> instance;

    boost::shared_ptr<IBlockFactory> blockFactory;

    std::string engineType;
    std::map<std::string, boost::function<boost::shared_ptr<IEngine> (boost::shared_ptr<IModel>, int, double)> > engineGenerators;

    std::string modelType;
    std::map<std::string, boost::shared_ptr<IModelGenerator> > modelTypes;

    std::map<std::string, boost::shared_ptr<IFileLoader> > fileLoaders; //loaders sorted by match regex

    std::string lastFileError;

};

#endif // SIMULATIONCORE_H
