TEMPLATE = lib

CONFIG = staticlib c++11
QMAKE_CXXFLAGS += -std=c++11


SOURCES += \
    Cone.cc\
    Frisbee.cc\
    Integrator.cc\
    IntegratorRK4.cc\
    Line.cc\
    Matrix3x3.cc\
    PlayingField.cc\
    System.cc\
    Vector3.cc



HEADERS += \
    Canvas.h\
    Cone.h\
    Drawable.h\
    Frisbee.h\
    Integrator.h\
    IntegratorRK4.h\
    Line.h\
    Matrix3x3.h\
    PlayingField.h\
    System.h\
    Vector3.h
