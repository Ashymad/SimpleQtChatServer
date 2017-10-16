#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T23:36:31
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       += network

TARGET = ChatServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    clienthandler.cpp \
    handlerfactory.cpp

HEADERS += \
    myserver.h \
    clienthandler.h \
    handlerfactory.h
