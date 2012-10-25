#-------------------------------------------------
#
# Project created by QtCreator 2012-10-01T22:03:19
#
#-------------------------------------------------

QT       += script svg xml xmlpatterns

TARGET = $$qtLibraryTarget(SystemBlocks)
TEMPLATE = lib

DESTDIR = ../../bin/plugins

DEFINES += SYSTEMBLOCKS_LIBRARY

SOURCES += systemblocks.cpp \
    varstatic.cpp \
    varramp.cpp

HEADERS += systemblocks.h\
        SystemBlocks_global.h \
    varstatic.h \
    varramp.h \
    ../../Engine/interfaces/iblockplugin.h \
    ../../Engine/interfaces/ipluginbase.h \
    ../../Engine/interfaces/iblockcore.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE211EE60
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = SystemBlocks.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
