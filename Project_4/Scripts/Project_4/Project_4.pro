TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ExpectationValues.cpp \
        Metropolis.cpp \
        PrepareSystem.cpp \
        ReadFiles.cpp \
        WriteResults.cpp \
        main.cpp

HEADERS += \
    ExpectationValues.h \
    Metropolis.h \
    PrepareSystem.h \
    ReadFiles.h \
    WriteResults.h
