#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T18:54:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Tile/mouseevent.h \
    Tile/tileclass.h \
    Files/boardDefinition.h \
    Files/alphaBetaSearch.h \
    Files/display.h \
    Files/evaluationFunction.h \
    Files/initialiseBoard.h \
    Files/player2CheckAndPlay.h \
    Files/successors.h \
    Files/terminalTest.h \
    Files/validPositionCheck.h

FORMS    += mainwindow.ui

DISTFILES += \
    Images/marble-piece-black.png \
    Images/marble-piece-white.png \
    Images/red.png \
    Images/redking.png \
    Images/white.png \
    Images/whiteking.png

