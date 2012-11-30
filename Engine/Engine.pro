#-------------------------------------------------
#
# Project created by QtCreator 2012-11-29T22:59:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = Engine
TEMPLATE = lib
CONFIG += staticlib

SOURCES += engine.cpp

HEADERS += engine.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
