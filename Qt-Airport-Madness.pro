#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T11:42:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-Airport-Madness
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamescene.cpp \
    planemodel.cpp \
    plane.cpp

HEADERS  += mainwindow.h \
    gamescene.h \
    planemodel.h \
    plane.h

FORMS    += mainwindow.ui

DISTFILES += \
    arts/level-1.png \
    arts/plane.png \
    levels/References/level-1-bezier-approach.lvl \
    levels/References/level-1-bkup.lvl \
    levels/References/level-1-old-map.lvl \
    levels/References/level-1-oldxml.lvl \
    arts/References/plane-black.jpg \
    arts/References/plane-white.jpg \
    arts/References/level-1-original.png \
    arts/References/plane2.png \
    levels/level-1.lvl

RESOURCES += \
    resources.qrc
