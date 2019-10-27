#ifndef PREPARESYSTEM_H
#define PREPARESYSTEM_H
#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;

class PrepareSystem
{
public:
    void PrepareSpinMatrix(int L);
    mat SpinSystem;

};

#endif // PREPARESYSTEM_H
