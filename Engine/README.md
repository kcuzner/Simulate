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

 * Computational block
 * Model block
 * Entry block
 * Exit block

### Computational Blocks

Computational blocks are the most basic level of any simulation. These
blocks encapsulate a class implementing IComputation which 

