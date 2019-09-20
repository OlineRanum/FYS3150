TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        External_Solvers.cpp \
        Jacobi_Method.cpp \
        MatrixMaker.cpp \
        PrepareResults.cpp \
        ReadFiles.cpp \
        main.cpp \
        tests.cpp
        lanczos_method.cpp \

LIBS += -llapack -lblas -larmadillo

HEADERS += \
    External_Solvers.h \
    Jacobi_Method.h \
    MatrixMaker.h \
    PrepareResults.h \
    ReadFiles.h \
    tests.h
    lanczos_method.h

DISTFILES += \
    ../build-Prosjekt_2-Desktop_Qt_5_13_0_GCC_64bit-Debug/N.txt \
    Prosjekt_2.pro.user
