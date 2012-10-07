#-------------------------------------------------
#
# Project created by QtCreator 2012-09-28T04:08:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulate
TEMPLATE = app

DESTDIR += ../bin

SOURCES += main.cpp\
        mainwindow.cpp \
    simulation/block.cpp \
    simulation/context.cpp \
    simulation/input.cpp \
    simulation/output.cpp \
    simulation/model.cpp \
    simulation/signalvalue.cpp \
    simulation/blockfactory.cpp \
    pluginsdialog.cpp \
    simulation/stepcontext.cpp

HEADERS  += mainwindow.h \
    simulation/block.h \
    simulation/context.h \
    simulation/input.h \
    simulation/output.h \
    simulation/model.h \
    simulation/signalvalue.h \
    simulation/blockfactory.h \
    simulation/blockplugin.h \
    pluginsdialog.h \
    simulation/stepcontext.h

FORMS    += mainwindow.ui \
    pluginsdialog.ui