######################################################################
# Automatically generated by qmake (2.01a) Sat Oct 20 21:26:20 2012
######################################################################

TEMPLATE = app
TARGET = Simulate
DESTDIR = ../bin
DEPENDPATH += . simulation
INCLUDEPATH += . simulation

# Input
HEADERS += ipluginbase.h \
           mainwindow.h \
           modeleditorwidget.h \
           modelwindow.h \
           pluginsdialog.h \
           plugintracker.h \
           simulation/block.h \
           simulation/blockfactory.h \
           simulation/context.h \
           simulation/entryblock.h \
           simulation/exitblock.h \
           simulation/iblockcore.h \
           simulation/iblockplugin.h \
           simulation/input.h \
           simulation/model.h \
           simulation/modelblock.h \
           simulation/output.h \
    simulation/iblockfactory.h
FORMS += mainwindow.ui modelwindow.ui pluginsdialog.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           modeleditorwidget.cpp \
           modelwindow.cpp \
           pluginsdialog.cpp \
           plugintracker.cpp \
           simulation/block.cpp \
           simulation/blockfactory.cpp \
           simulation/context.cpp \
           simulation/entryblock.cpp \
           simulation/exitblock.cpp \
           simulation/input.cpp \
           simulation/model.cpp \
           simulation/modelblock.cpp \
           simulation/output.cpp
