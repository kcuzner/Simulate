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
    componenttracker.cpp

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
    interfaces/icomponent.h \
    componenttracker.h \
    interfaces/icomponenttracker.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:LIBS += -lboost
