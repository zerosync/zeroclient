#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T23:25:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZeroSyncDesktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zsfilesystemwatcher.cpp

HEADERS  += mainwindow.h \
    zsfilesystemwatcher.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    ZeroSyncResources.qrc
