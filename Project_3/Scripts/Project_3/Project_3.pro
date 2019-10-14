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
QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK



SOURCES += \
        GaussLaguerre.cpp \
        GaussLegendre.cpp \
        MonteCarloIntegration.cpp \
        ReadFiles.cpp \
        WriteResults.cpp \
        main.cpp

HEADERS += \
    GaussLaguerre.h \
    GaussLegendre.h \
    MonteCarloIntegration.h \
    ReadFiles.h \
    WriteResults.h