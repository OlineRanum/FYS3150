#ifndef PREPARESYSTEM_H
#define PREPARESYSTEM_H
#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;

class PrepareSystem
{
public:
    void PrepareSpinMatrix_Random(int L);
    void PrepareSpinMatrix_Ordered(int L, int mode);
    mat SpinSystem;

};

#endif // PREPARESYSTEM_H
