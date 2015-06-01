#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T20:33:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StickmanAssignment
TEMPLATE = app


SOURCES += main.cpp\
        gamedialog.cpp \
    config.cpp \
    stickman.cpp \
    background.cpp \
    cloud.cpp \
    hills.cpp \
    positioninterface.cpp \
    drawablefactory.cpp \
    drawable.cpp \
    obstacle.cpp \
    stickmanproxy.cpp \
    configurablescene.cpp \
    powerup.cpp \
    stickmanstate.cpp \
    stickmanstategiant.cpp \
    stickmanstatelarge.cpp \
    stickmanstatetiny.cpp \
    stickmanstatenormal.cpp \
    stickmanstatepower.cpp \
    tests.cpp \
    enemy.cpp

HEADERS  += gamedialog.h \
    config.h \
    stickman.h \
    background.h \
    cloud.h \
    hills.h \
    positioninterface.h \
    drawablefactory.h \
    drawable.h \
    obstacle.h \
    stickmanproxy.h \
    configurablescene.h \
    powerup.h \
    tests.h \
    enemy.h

FORMS    += gamedialog.ui

QMAKE_CXXFLAGS += -std=c++0x

DISTFILES += \
    Game.config
