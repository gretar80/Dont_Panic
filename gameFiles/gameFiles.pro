#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T11:06:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gameFiles
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    gamewindow.cpp \
    gamegrid.cpp \
    bombsignaller.cpp \
    player.cpp \
    bomb.cpp \
    highscorewindow.cpp \
    gameovernohighscore.cpp \
    gameovernewhighscore.cpp

HEADERS  += mainwindow.h \
    gamewindow.h \
    bomb.h \
    gamegrid.h \
    bombsignaller.h \
    player.h \
    highscorewindow.h \
    gameovernohighscore.h \
    gameovernewhighscore.h

FORMS    += mainwindow.ui \
    gamewindow.ui \
    highscorewindow.ui \
    gameovernohighscore.ui \
    gameovernewhighscore.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
