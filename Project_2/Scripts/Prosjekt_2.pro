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
        n_text_timer.cpp \
        tests.cpp \
        lanczos_method.cpp \

LIBS += -llapack -lblas -larmadillo

HEADERS += \
    External_Solvers.h \
    Jacobi_Method.h \
    MatrixMaker.h \
    PrepareResults.h \
    ReadFiles.h \
    n_text_timer.h \
    tests.h \
    lanczos_method.h

DISTFILES += \
    Prosjekt_2.pro.user
