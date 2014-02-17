#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T23:25:31
#
#-------------------------------------------------

QT       += core gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZeroSyncDesktop
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    zsfilesystemwatcher.cpp \
    zsdatabase.cpp \
    zsindex.cpp \
    zsfilemetadata.cpp \
    zssettings.cpp \
    zssetupwizard.cpp \
    zssyncwizardpage.cpp \
    zsdirectorywizardpage.cpp \
    zsconnector.cpp \
    zstree.cpp \
    zshtmlbuilder.cpp

HEADERS  += mainwindow.h \
    zsfilesystemwatcher.h \
    zsdatabase.h \
    zsindex.h \
    zsfilemetadata.h \
    zssettings.h \
    zssetupwizard.h \
    zssyncwizardpage.h \
    zsdirectorywizardpage.h \
    zsconnector.h \
    zstree.h \
    zshtmlbuilder.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    ZeroSyncResources.qrc

QMAKE_CXXFLAGS += -std=c++11

unix:!macx: LIBS += -L/usr/local/lib/ -lczmq

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libczmq.a

unix:!macx: LIBS += -L/usr/local/lib/ -lsodium

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libsodium.a

unix:!macx: LIBS += -L/usr/local/lib/ -lzmq

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libzmq.a

unix:!macx: LIBS += -L/usr/local/lib/ -lzsync

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libzsync.a

unix:!macx: LIBS += -L/usr/local/lib/ -lzyre

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libzyre.a
