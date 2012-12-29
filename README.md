Simulate
========

A mathematical modeling and simulation framework.

By Kevin Cuzner

Motivation
----------

Owing to the lack of open-source simulation software, it was decided to
write this piece of software. It is divided into several parts:

 * *The Engine library*
   > This holds the definition of the interfaces to the engine along with the
   > default system blocks. It depends on the boost library for smart pointers,
   > testing, threading, and other things.
 * *The Console application*
   > This is an implementation of the engine in a console application format
   > which uses the Qt framework for file processing.
 * *The GUI application*
   > This is an implementation of the engine in a GUI application format which
   > uses the Qt framework for just about everything. This can be considered to
   > be the main editor.
 * *Tests*
   > This project contains tests structured around boost test.

Details of exact operation of each component can be found in their respective
files.

