TEMPLATE = lib

CONFIG = staticlib c++11
QMAKE_CXXFLAGS += -std=c++11


SOURCES += \
    Frisbee.cc\
    Integrator.cc\
    IntegratorRK4.cc\
    Matrix3x3.cc\
    System.cc\
    Vector3.cc



HEADERS += \
    Canvas.h\
    Drawable.h\
    Frisbee.h\
    Integrator.h\
    IntegratorRK4.h\
    Matrix3x3.h\
    System.h\
    Vector3.h
