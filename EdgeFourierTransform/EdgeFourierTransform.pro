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
    FourierTransform.cpp \
    EdgeBuilder.cpp \
    FourierLowPassFilter.cpp

HEADERS  += MainWindow.h \
    Edge.h \
    EdgeView.h \
    Fourier.h \
    FourierTransform.h \
    IFourierTransform.h \
    EdgeBuilder.h \
    IFourierFilter.h \
    FourierLowPassFilter.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    EdgeFourierTransform.pro.user
