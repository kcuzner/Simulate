#ifndef ISIMULATION_H
#define ISIMULATION_H

#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "iengine.h"

/**
 * @brief Class containing an engine and other such things which
 * is created from a file
 */
class ISimulation
{
public:
    virtual ~ISimulation() {}

    virtual bool isFileNameSet() const = 0;
    virtual void setFileName(const std::string& fileName) = 0;
    virtual const std::string& getFileName() const = 0;

    virtual int getSteps() const = 0;
    virtual void setSteps(int steps) = 0;

    virtual double getDelta() const = 0;
    virtual void setDelta(double delta) = 0;

    virtual boost::shared_ptr<IModel> getRootModel() = 0;
    virtual bool setRootModel(const std::string& name) = 0;

    virtual const std::map<std::string, boost::shared_ptr<IModel> >& getModels() = 0;

    virtual boost::shared_ptr<IModel> getModel(const std::string& name) = 0;

    virtual bool addModel(boost::shared_ptr<IModel> model) = 0;
    virtual bool removeModel(const std::string& name) = 0;

    virtual bool isChanged() = 0;
    virtual void resetChanged() = 0;

    //bubbled events
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>)> sigBlockChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, const std::string&, boost::shared_ptr<IBlock>, const std::string&)> sigBlockConnected;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, const std::string&)> sigBlockOptionChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, const std::string&)> sigBlockDataChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockInput>)> sigBlockInputAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockInput>)> sigBlockInputRemoved;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockOutput>)> sigBlockOutputAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>, boost::shared_ptr<IBlockOutput>)> sigBlockOutputRemoved;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>)> sigModelChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, const std::string&)> sigModelNameChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IEntryBlock>)> sigModelEntryAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IEntryBlock>)> sigModelEntryRemoved;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IExitBlock>)> sigModelExitAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IExitBlock>)> sigModelExitRemoved;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>)> sigModelBlockAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>, boost::shared_ptr<IBlock>)> sigModelBlockRemoved;

    //simulation events
    boost::signals2::signal<void (ISimulation*)> sigSimulationChanged;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>)> sigModelAdded;
    boost::signals2::signal<void (ISimulation*, boost::shared_ptr<IModel>)> sigModelRemoved;
    boost::signals2::signal<void (ISimulation*, double)> sigDeltaChanged;
    boost::signals2::signal<void (ISimulation*, int)> sigStepsChanged;

};

#endif // ISIMULATION_H
