#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T04:31:34
#
#-------------------------------------------------

QT       -= gui

TARGET = FourierTransform
TEMPLATE = lib

DEFINES += FOURIERTRANSFORM_LIBRARY

SOURCES += \
    FourierTransform.cpp \
    FourierLowPassFilter.cpp \
    FastFourierTransform.cpp \
    ComplexMatrix.cpp

HEADERS += \
    FourierTransform_Global.h \
    IFourierFilter.h \
    IFourierTransform.h \
    FourierTransform.h \
    FourierLowPassFilter.h \
    FastFourierTransform.h \
    Fourier.h \
    ComplexMatrix.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
