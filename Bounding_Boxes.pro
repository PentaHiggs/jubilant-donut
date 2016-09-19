#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T01:52:49
#
#-------------------------------------------------
QT  +=  core \
        gui \
        network \
        xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app

!testcase {
    TARGET = Bounding_Boxes
    SOURCES += src\main.cpp
}

SOURCES += src\window_main.cpp \
    src\imagedownloader.cpp \
    src\xmlimageloader.cpp \
    src\labeledimage.cpp \
    src\imagelabelingscene.cpp \
    src\xmlimagesaver.cpp \
    src\projectivetransform.cpp

HEADERS  += src\window_main.h \
    src\imagedownloader.h \
    src\xmlimageloader.h \
    src\labeledimage.h \
    src\imagelabelingscene.h \
    src\xmlimagesaver.h \
    src\projectivetransform.h



testcase {
    TARGET  += Bounding_Boxes_Tests
    QT      += testlib
    SOURCES += test\test_projectivetransform.cpp
    HEADERS += test\test_projectivetransform.h
}

FORMS    += src\window_main.ui

INCLUDEPATH += E:\Eigen\include\eigen3

DISTFILES += \
    picture_batch.xsd

RESOURCES = application.qrc 
