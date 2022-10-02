QT += core gui opengl widgets

CONFIG += c++11

win32:LIBS += -lopengl32

TARGET = Projet_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    CommandWindow.cc\
    GLSphere.cc\
    GLWidget.cc \
    InfoWindow.cc \
    main_qt_gl.cc \
    OpenGLViewer.cc\
    PosInfo.cc 

HEADERS += \
    CommandWindow.h\
    GLSphere.h\
    GLWidget.h \
    InfoWindow.h \
    main_qt_gl.h \
    OpenGLViewer.h\
    PosInfo.h \
    VertexShader.h

RESOURCES += \
    resource.qrc
