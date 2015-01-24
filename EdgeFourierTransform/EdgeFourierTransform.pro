#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T16:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EdgeFourierTransform
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Edge.cpp \
    EdgeFT.cpp \
    EdgeView.cpp \
    FourierTransform.cpp

HEADERS  += MainWindow.h \
    Edge.h \
    EdgeFT.h \
    EdgeView.h \
    Fourier.h \
    FourierTransform.h \
    IFourierTransform.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    EdgeFourierTransform.pro.user
