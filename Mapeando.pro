#-------------------------------------------------
#
# Project created by QtCreator 2015-04-21T10:09:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mapeando
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    crobot.cpp \
    mapa.cpp \
    trigonometria.cpp \
    brain_mapping.cpp \
    thread_robot.cpp

HEADERS  += mainwindow.h \
    crobot.h \
    mapa.h \
    trigonometria.h \
    brain_mapping.h \
    thread_robot.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/Aria/include

LIBS += -L/usr/local/Aria/lib/ \
    -lAria -ldl -lrt -lm


