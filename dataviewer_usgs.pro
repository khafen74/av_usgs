#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T20:19:25
#
#-------------------------------------------------

QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataviewer_usgs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloadmanager.cpp \
    urlgenerator.cpp \
    qcustomplot.cpp \
    dialog_loaddata.cpp \
    dialog_selectdata.cpp \
    dialog_loadsites.cpp

HEADERS  += mainwindow.h \
    downloadmanger.h \
    urlgenerator.h \
    qcustomplot.h \
    dialog_loaddata.h \
    dialog_selectdata.h \
    dialog_loadsites.h

FORMS    += mainwindow.ui \
    dialogloaddata.ui \
    dialogselectdata.ui \
    dialog_loaddata.ui \
    dialog_selectdata.ui \
    dialog_loadsites.ui
