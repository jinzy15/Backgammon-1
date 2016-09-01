#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T15:35:35
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Backgammon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    connectdialog.h

FORMS    += mainwindow.ui \
    dialog.ui \
    connectdialog.ui
