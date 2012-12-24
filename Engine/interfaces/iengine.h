#ifndef IENGINE_H
#define IENGINE_H

#include <boost/smart_ptr.hpp>
#include <boost/signals2.hpp>

#include "imodel.h"
#include "iblockfactory.h"

/**
 * @brief Interface to the simulation engine
 *
 * This library supplies one default simulation engine: A multithreaded "simple"
 * engine. An engine is used to run a simulation by feeding in the top level model.
 * Unless the engine explicitly says that it can, modifying the model during a
 * simulation should be avoided.
 *
 * A general rule of thumb should be that engines can run models and blocks of
 * any implementation, but they may implement special run methods for specialized
 * models and blocks which may be specific to that engine.
 */
class IEngine
{
public:
    virtual ~IEngine() {}

    /**
     * @brief Returns the number of steps which constitute a "run"
     * @return
     */
    virtual unsigned int getStepsToRun() = 0;
    /**
     * @brief Sets the number of steps which constitute a "run"
     * @param n
     */
    virtual void setStepsToRun(unsigned int n) = 0;

    /**
     * @brief Gets the delta to increment the time constant by after each step
     * @return
     */
    virtual double getStepDelta() = 0;
    /**
     * @brief Sets the delta to increment the time constant by after each step
     * @param d
     */
    virtual void setStepDelta(double d) = 0;

    /**
     * @brief Returns the context for this engine. This should be used when setting options for the blocks in the root level model.
     * @return
     */
    virtual boost::shared_ptr<IContext> getContext() = 0;

    /**
     * @brief Returns the model that this engine simulates. Note that a model may have multiple
     * engines but an engine may have only one model attached.
     * @return
     */
    virtual boost::shared_ptr<IModel> getRootModel() = 0;

    /**
     * @brief Runs the model attached to this engine.
     * @param model
     */
    virtual void run() = 0;

    /**
     * @brief Returns the block factory for this engine
     * @return
     */
    virtual boost::shared_ptr<IBlockFactory> getBlockFactory() = 0;

    /**
     * @brief Signal emitted when a step completes. Second argument is step number completed, third is total steps
     */
    boost::signals2::signal<void (boost::shared_ptr<IModel>, int, int)> sigStepCompleted;
};

#endif // IENGINE_H
