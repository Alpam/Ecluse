#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T21:08:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ecluse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    automatique.cpp \
    expert.cpp

HEADERS  += mainwindow.h \
    automatique.h \
    expert.h

FORMS    += mainwindow.ui \
    automatique.ui \
    expert.ui