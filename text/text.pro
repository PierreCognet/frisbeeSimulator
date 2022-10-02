CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

TARGET = Projet_Text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    TextViewer.cc

HEADERS += \
    TextViewer.h \
