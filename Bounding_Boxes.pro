#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T01:52:49
#
#-------------------------------------------------
QT       += core
QT       += core gui
QT       += network
QT       += xmlpatterns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bounding_Boxes
TEMPLATE = app


SOURCES += main.cpp\
        window_main.cpp \
    imagedownloader.cpp \
    xmlimageloader.cpp \
    labeledimage.cpp \
    imagelabelingscene.cpp \
    xmlimagesaver.cpp

HEADERS  += window_main.h \
    imagedownloader.h \
    xmlimageloader.h \
    labeledimage.h \
    imagelabelingscene.h \
    xmlimagesaver.h

FORMS    += window_main.ui

INCLUDEPATH += E:\Eigen\include\eigen3

DISTFILES += \
    picture_batch.xsd

RESOURCES = application.qrc \
    application.qrc
