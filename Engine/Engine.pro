#-------------------------------------------------
#
# Project created by QtCreator 2012-11-29T22:59:20
#
#-------------------------------------------------

QT -= core gui

TARGET = Engine
DESTDIR = ../lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    model.cpp \
    defaultblockfactory.cpp \
    modelblock.cpp \
    baseblock.cpp \
    baseblockinput.cpp \
    baseblockoutput.cpp \
    defaultcontext.cpp \
    simpleengine.cpp \
    entryblock.cpp \
    exitblock.cpp \
    system/varstatic.cpp \
    system/systemblocks.cpp \
    system/varramp.cpp \
    system/mathmultiply.cpp \
    simulationcore.cpp \
    xmlfileloader.cpp

HEADERS += \
    model.h \
    interfaces/iblock.h \
    interfaces/iblockfactory.h \
    interfaces/imodel.h \
    interfaces/ientryblock.h \
    interfaces/iexitblock.h \
    interfaces/icontext.h \
    interfaces/iblockinput.h \
    interfaces/iblockoutput.h \
    defaultblockfactory.h \
    modelblock.h \
    baseblock.h \
    baseblockinput.h \
    baseblockoutput.h \
    interfaces/iblockio.h \
    interfaces/imodelblock.h \
    defaultcontext.h \
    interfaces/iengine.h \
    simpleengine.h \
    entryblock.h \
    exitblock.h \
    system/varstatic.h \
    interfaces/iblockcollection.h \
    system/systemblocks.h \
    system/varramp.h \
    system/mathmultiply.h \
    interfaces/ifilemodeldescription.h \
    interfaces/ifileloader.h \
    interfaces/ifileblockdescription.h \
    interfaces/isimulation.h \
    simulationcore.h \
    interfaces/isimulationcore.h \
    xmlfileloader.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:LIBS += -lboost
