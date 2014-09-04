#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T21:16:00
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CG1

CONFIG += c++11
#CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
	src/main.cpp \
	src/model.cpp \
    src/janelaprincipal.cpp \
    src/janelagl.cpp

HEADERS += \
    src/model.h \
    src/janelaprincipal.h \
    src/janelagl.h

FORMS += \
    src/janelaprincipal.ui
