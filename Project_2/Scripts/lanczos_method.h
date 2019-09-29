#ifndef LANCZOS_METHOD_H
#define LANCZOS_METHOD_H

#include <armadillo>

using namespace arma;

class Lanczos_method
{
public:
    void Lanczos(int, double *, double *, int, int *, double *, mat, mat &);
};

#endif // LANCZOS_METHOD_H
