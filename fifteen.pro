QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = fifteen
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += Board.h MainWindow.h
SOURCES += Board.cpp main.cpp MainWindow.cpp
