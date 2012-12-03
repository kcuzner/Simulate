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

