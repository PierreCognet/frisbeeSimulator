QT += core gui opengl widgets

CONFIG += c++11

win32:LIBS += -lopengl32

TARGET = Projet_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    GLSphere.cc\
    InfoWindow.cc\
    KeyActionWindow.cc\
    MainWindow.cc\
    main_qt_gl.cc\
    MovieRecorder.cc\
    OpenGLViewer.cc\
    Playback.cc\
    PosInfo.cc\
    Visual3DWindow.cc\
    VisualSimulation.cc

HEADERS += \
    GLSphere.h\
    InfoWindow.h\
    KeyActionWindow.h\
    MainWindow.h\
    main_qt_gl.h\
    MovieRecorder.h\
    OpenGLViewer.h\
    PosInfo.h\
    Playback.h\
    VertexShader.h\
    Visual3DWindow.h\
    VisualSimulation.h

RESOURCES += \
    resource.qrc
