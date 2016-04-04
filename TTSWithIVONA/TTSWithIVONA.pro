#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T13:48:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TTSWithIVONA
TEMPLATE = app
CONFIG+=crypto

INCLUDEPATH += C:/OpenSSL-Win32/include
LIBS += -LC:/OpenSSL-Win32/lib -lubsec

SOURCES += main.cpp\
        mainwindow.cpp \
    ivonaclient.cpp

HEADERS  += mainwindow.h \
    ivonaclient.h

FORMS    += mainwindow.ui
