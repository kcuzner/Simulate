Simulation Engine
=================

This is a statically linked library which provides the basic functionality
to run a simulation.

Simulation Description:
-----------------------

A simulation is described in terms of models. A model contains a set of
computational blocks interlinked by connections. The top level model of a
simulation is considered to be its entry point. The following basic types
of blocks are supplied by the engine:

 * Model block
 * Entry block
 * Exit block
 * Basic system computation blocks

Running simulations
-------------------

A simulation is run by creating an object implementing IContext and passing
it a model to run. In the default implementation here, the sequence is as
follows:

 1) If this is the first time this model is being run, have all the blocks
    initialize themselves to the context
 2) Run all blocks with no inputs (i.e. entry blocks, variable blocks, etc)
 3) As the blocks run, they should be setting their outputs through the
    context. This will in turn, cause the rest of the blocks to be added to
    an execution queue. This execution queue may be run in another thread.
 4) When the execution queue is emptied and all blocks in it have been run,
    the step is considered completed.
 5) All the entry blocks with matching exit block names are asked through
    an entryblock specific method to set their next output value for the
    context to be the input value of the corrisponding exit.
 6) The method returns

In a context, running each individual block is accomplished as follows:

 1) Run the initialize method passing in the context
 2) Run the execute method passing in the context
 3) When the block asks to set an output to a specific value, make note
    of which inputs are connected to the passed output and "set" their
    values in the context. For each input, if setting that input has caused
    all the inputs for the block to be assigned, queue the block for
    execution.

To do list
----------

 * Figure out block tracking
  * Model level tracking instead of engine level tracking. If we assume there
    is one context per model then the model can track the block ids. The
    model gets to call the block factory. When a model is created, it can
    either do its own block creation through a singleton of a block factory or
    it could get passed in a block factory to use.
  * Inputs and outputs are tracked on a per-block basis. In the files and other
    things they are referenced solely by name, but to speed things up they will
    be stored by an integer id that is unique over the lifetime of the block
    they are assigned to. The block should always return weak pointers to its
    inputs/outputs and strong references to them should be very temporary so that
    when the block is destroyed its ios go away.
  * The DefaultContext 
 * Resolve whether or not block ids are longs or int. Make this consistent
 * Make a triggering mechanism for blocks so they don't always have to be executed.
 * Build a loader (possibly a separate qt plugin...at least make the interface)
  * The sequence for loading:
    1) Scan the file for all model definitions
    2) For each model, create it with only the entry and exit blocks. This
       makes modelblocks possible with partial model definitions.
    3) Then in any order, add the additional blocks to each model until the file
       is loaded.


