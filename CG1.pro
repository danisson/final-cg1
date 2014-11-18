#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T21:16:00
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CG1

CONFIG += c++11
CONFIG += static
#CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
	src/main.cpp \
	src/model.cpp \
    src/transformmatrix.cpp \
    src/janelaprincipal.cpp \
    src/janelagl.cpp \
    src/colormatrix.cpp \
    src/light.cpp

HEADERS += \
    src/model.h \
    src/transformmatrix.h \
    src/janelaprincipal.h \
    src/janelagl.h \
    src/colormatrix.h \
    src/light.h

FORMS += \
    src/janelaprincipal.ui
