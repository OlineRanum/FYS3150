TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

QMAKE_CFLAGS += $$system(mpicc --showme:compile)
QMAKE_LFLAGS += $$system(mpicxx --showme:link)
QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK-O2
QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK


SOURCES += \
        EvaluateSystem.cpp \
        ExpectationValues.cpp \
        Metropolis.cpp \
        PrepareSystem.cpp \
        ReadFiles.cpp \
        WriteResults.cpp \
        main.cpp

HEADERS += \
    EvaluateSystem.h \
    ExpectationValues.h \
    Metropolis.h \
    PrepareSystem.h \
    ReadFiles.h \
    WriteResults.h
