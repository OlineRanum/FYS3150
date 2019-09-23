TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    1A_analytical_solution.cpp \
    1A_fh.cpp \
    1B_general_alg.cpp \
    1C_specialised_alg.cpp \
    1E_lu_decomp.cpp \
    INACTIVE_1D_rel_error.cpp \
    main.cpp \

LIBS += -llapack -lblas -larmadillo

HEADERS +=
