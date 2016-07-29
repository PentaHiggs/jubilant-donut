#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T01:52:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bounding_Boxes
TEMPLATE = app


SOURCES += main.cpp\
        window_main.cpp \
    imagedownloader.cpp \
    xmlimageloader.cpp \
    labeledimage.cpp \
    imagelabellingscene.cpp

HEADERS  += window_main.h \
    imagedownloader.h \
    xmlimageloader.h \
    labeledimage.h \
    imagelabellingscene.h

FORMS    += window_main.ui

INCLUDEPATH += $$PWD/Eigen/

DISTFILES += \
    picture_batch.xsd

RESOURCES = application.qrc \
    application.qrc
