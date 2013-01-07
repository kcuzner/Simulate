#ifndef SIMULATION_H
#define SIMULATION_H

#include "interfaces/isimulation.h"

#include <map>

class Simulation : public ISimulation
{
public:
    Simulation(int steps, double delta);
    Simulation(int steps, double delta, const std::string& fileName);

    virtual bool isFileNameSet() const;
    virtual void setFileName(const std::string& fileName);
    virtual const std::string& getFileName() const;

    virtual int getSteps() const;
    virtual void setSteps(int steps);

    virtual double getDelta() const;
    virtual void setDelta(double delta);

    virtual boost::shared_ptr<IModel> getRootModel();
    virtual bool setRootModel(const std::string& name);

    virtual const std::map<std::string, boost::shared_ptr<IModel> >& getModels();

    virtual boost::shared_ptr<IModel> getModel(const std::string& name);

    virtual bool addModel(boost::shared_ptr<IModel> model);
    virtual bool removeModel(const std::string& name);

    virtual bool isChanged();
    virtual void resetChanged();

protected:
    std::map<std::string, boost::shared_ptr<IModel> > models;
    std::string rootModelName;

    bool simulationChanged;

    bool fileNameSet;
    std::string fileName;
    int steps;
    double delta;

    void onBlockChanged(IModel* model, boost::shared_ptr<IBlock> block);
    void onBlockConnected(IModel* model, boost::shared_ptr<IBlock> block, const std::string& output, boost::shared_ptr<IBlock> toBlock, const std::string& input);
    void onBlockOptionChanged(IModel* model, boost::shared_ptr<IBlock> block, const std::string& name);
    void onBlockDataChanged(IModel* model, boost::shared_ptr<IBlock> block, const std::string& name);
    void onBlockInputAdded(IModel* model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockInput> input);
    void onBlockInputRemoved(IModel* model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockInput> input);
    void onBlockOutputAdded(IModel* model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockOutput> output);
    void onBlockOutputRemoved(IModel* model, boost::shared_ptr<IBlock> block, boost::shared_ptr<IBlockOutput> output);
    void onModelChanged(IModel* model);
    void onModelNameChanged(IModel* model, const std::string& name);
    void onModelEntryAdded(IModel* model, boost::shared_ptr<IEntryBlock> entry);
    void onModelEntryRemoved(IModel* model, boost::shared_ptr<IEntryBlock> entry);
    void onModelExitAdded(IModel* model, boost::shared_ptr<IExitBlock> exit);
    void onModelExitRemoved(IModel* model, boost::shared_ptr<IExitBlock> exit);
    void onModelBlockAdded(IModel* model, boost::shared_ptr<IBlock> block);
    void onModelBlockRemoved(IModel* model, boost::shared_ptr<IBlock> block);
};

#endif // SIMULATION_H
