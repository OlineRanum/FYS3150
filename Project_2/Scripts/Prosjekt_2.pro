TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Read_N_from_file.cpp \
        main.cpp \
        matrix.cpp

LIBS += -llapack -lblas -larmadillo

HEADERS += \
    Read_N_from_file.h \
    matrix.h
