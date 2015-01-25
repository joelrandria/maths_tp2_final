#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T04:56:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageFourierTransform
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/release/ -lFourierTransform
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/debug/ -lFourierTransform
else:unix: LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/ -lFourierTransform

INCLUDEPATH += $$PWD/../FourierTransform
DEPENDPATH += $$PWD/../FourierTransform
