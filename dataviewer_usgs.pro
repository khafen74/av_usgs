#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T20:19:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataviewer_usgs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloadmanager.cpp

HEADERS  += mainwindow.h \
    downloadmanger.h

FORMS    += mainwindow.ui
