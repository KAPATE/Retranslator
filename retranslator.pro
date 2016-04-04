#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T14:44:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = retranslator
TEMPLATE = app

CONFIG += c++14 console

SOURCES += main.cpp\
        mainwindow.cpp \
    analyzer.cpp

HEADERS  += mainwindow.h \
    analyzer.h

FORMS    += mainwindow.ui

