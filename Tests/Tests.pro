TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test_defaultfactory.cpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:LIBS += -lboost_unit_test_framework

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lEngine
else:unix: LIBS += -L$$PWD/../lib/ -lEngine

INCLUDEPATH += $$PWD/../Engine
DEPENDPATH += $$PWD/../Engine

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/Engine.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/Engine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/libEngine.a

