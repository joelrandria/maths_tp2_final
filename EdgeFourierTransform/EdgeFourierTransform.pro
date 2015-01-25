#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T16:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EdgeFourierTransform
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS +=  -std=c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    Edge.cpp \
    EdgeView.cpp \
    EdgeBuilder.cpp

HEADERS  += MainWindow.h \
    Edge.h \
    EdgeView.h \
    EdgeBuilder.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    EdgeFourierTransform.pro.user

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/release/ -lFourierTransform
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/debug/ -lFourierTransform
else:unix: LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/ -lFourierTransform

INCLUDEPATH += $$PWD/../FourierTransform
DEPENDPATH += $$PWD/../FourierTransform
