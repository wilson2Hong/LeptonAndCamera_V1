#-------------------------------------------------
#
# Project created by QtCreator 2018-12-05T22:22:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LeptonAndCamera

RPI_LIBS = ../raspberrypi_libs
LEPTONSDK = leptonSDKEmb32PUB

PRE_TARGETDEPS += sdk
QMAKE_EXTRA_TARGETS += sdk sdkclean
sdk.commands = make -C $${RPI_LIBS}/$${LEPTONSDK}
sdkclean.commands = make -C $${RPI_LIBS}/$${LEPTONSDK} clean

DEPENDPATH += .
INCLUDEPATH += . $${RPI_LIBS}

DESTDIR=.
OBJECTS_DIR=gen_objs
MOC_DIR=gen_mocs

unix:LIBS += -L$${RPI_LIBS}/$${LEPTONSDK}/Debug -lLEPTON_SDK

unix:QMAKE_CLEAN += -r $(OBJECTS_DIR) $${MOC_DIR}


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

SOURCES += main.cpp \
        leptonandcamera.cpp \
        LeptonThread.cpp \
        SPI.cpp \
        Palettes.cpp \
        MyLabel.cpp \
        Lepton_I2C.cpp

HEADERS  += \
         leptonandcamera.h \
         LeptonThread.h \
         SPI.h \
         Palettes.h \
         MyLabel.h \
         Lepton_I2C.cpp

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \
                /usr/local/include/raspicam

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_video.so \
        /usr/local/lib/libopencv_videostab.so \
        -L/usr/local/lib \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_video \
        -lopencv_videostab \

LIBS += -lwiringPi


FORMS    += leptonandcamera.ui
