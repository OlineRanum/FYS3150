#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


class MatrixMaker
{
public:
    void Tridiag(double h, int N,  double* lambda_analytical);
    void Tridiag_QD1e(double h, int N, double* rho);
    int N;
    mat A; mat A_copy;
    mat A_q;
private:
    double a;
    double d;
};

#endif // MATRIX_H
