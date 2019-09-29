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
    void Tridiag_QD_1e(double h, int N, double* rho);
    void Tridiag_QD_2e(double h, int N, double* rho, double omega_r);
    void Make_Identity(int N);

    int N;
    mat A; mat A_copy;
    mat A_q; mat A_q_2e;
    mat I;
private:
    double a;
    double d;
};

#endif // MATRIX_H
