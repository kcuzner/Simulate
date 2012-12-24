#-------------------------------------------------
#
# Project created by QtCreator 2012-11-29T23:00:10
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Console
CONFIG   += console
CONFIG   -= app_bundle

SUBDIRS += ../Engine

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lEngine
else:unix: LIBS += -L$$PWD/../lib/ -lEngine

INCLUDEPATH += $$PWD/../Engine
DEPENDPATH += $$PWD/../Engine

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/Engine.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/Engine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/libEngine.a
