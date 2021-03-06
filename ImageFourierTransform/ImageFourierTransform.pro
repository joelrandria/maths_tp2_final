#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T04:56:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageFourierTransform
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS +=  -std=c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    Image.cpp \
    Fourier2DFilter.cpp \
    Fourier2DFilterView.cpp

HEADERS  += MainWindow.h \
    Image.h \
    Fourier2DFilter.h \
    Fourier2DFilterView.h

FORMS    += MainWindow.ui \
    Fourier2DFilter.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/release/ -lFourierTransform
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/debug/ -lFourierTransform
else:unix: LIBS += -L$$PWD/../build-FourierTransform-Desktop-Debug/ -lFourierTransform

INCLUDEPATH += $$PWD/../FourierTransform
DEPENDPATH += $$PWD/../FourierTransform

RESOURCES += \
    ImageFourier.qrc
