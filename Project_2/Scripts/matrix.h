#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

class Matrix
{
public:
    void Tridiag(double h, int N,  double* lambda_);
    void Similar(int N, double k, double l, double s, double c);
    void Jacobi(int N);

    int N;
    mat matr_A;
    mat sim;
    double a;
    double d;
private:
};

#endif // MATRIX_H
