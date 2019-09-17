TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ReadFiles.cpp \
        main.cpp \
        matrix.cpp \
        prepare_results.cpp

LIBS += -llapack -lblas -larmadillo

HEADERS += \
    ReadFiles.h \
    matrix.h \
    prepare_results.h
