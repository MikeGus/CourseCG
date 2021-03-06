#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T12:53:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseCG
TEMPLATE = app

QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS_RELEASE += -O3

CONFIG += static

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    edge.cpp \
    flatness.cpp \
    point.cpp \
    prism.cpp \
    light.cpp \
    camera.cpp \
    qprismdialog.cpp \
    manager.cpp \
    beam.cpp \
    utils.cpp \
    beam_tree.cpp

HEADERS += \
        mainwindow.h \
    edge.h \
    point.h \
    flatness.h \
    prism.h \
    camera.h \
    light.h \
    manager.h \
    qprismdialog.h \
    sceneobject.h \
    beam.h \
    utils.h \
    beam_tree.h

FORMS += \
        mainwindow.ui
