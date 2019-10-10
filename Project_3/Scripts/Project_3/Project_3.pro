TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        GaussLaguerre.cpp \
        GaussLegendre.cpp \
        ReadFiles.cpp \
        WriteResults.cpp \
        main.cpp

HEADERS += \
    GaussLaguerre.h \
    GaussLegendre.h \
    ReadFiles.h \
    WriteResults.h
