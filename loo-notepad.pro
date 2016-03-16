#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T10:58:22
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = loo-notepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finder.cpp \
    replace.cpp

HEADERS  += mainwindow.h \
    finder.h \
    replace.h

FORMS    += mainwindow.ui \
    finder.ui \
    replace.ui
