#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T21:59:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PipeSquare
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpu.cpp \
    instruction.cpp \
    memory.cpp \
    parser.cpp \
    registerfile.cpp \
    controlunit.cpp

HEADERS  += mainwindow.h \
    cpu.h \
    instruction.h \
    memory.h \
    parser.h \
    registerfile.h \
    controlunit.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
