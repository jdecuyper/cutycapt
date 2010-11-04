#-------------------------------------------------
#
# Project created by QtCreator 2010-10-12T16:44:29
#
#-------------------------------------------------

QT       += core webkit svg network

TARGET = CutyCapt
CONFIG   += qt console

CONFIG   -= app_bundle

contains(CONFIG, static): {
  QTPLUGIN += qjpeg qgif qsvg qmng qico qtiff
  DEFINES  += STATIC_PLUGINS
}

SOURCES += main.cpp \
    CutyCapt.cpp \
    CutyPage.cpp \
    CutyHelp.cpp \
    CutyArgs.cpp \
    CutyTimer.cpp \
    CutyUtil.cpp

HEADERS += \
    CutyCapt.h \
    CutyPage.h \
    CutyHelp.h \
    CutyExt.h \
    CutyArgs.h \
    CutyTimer.h \
    CutyUtil.h
