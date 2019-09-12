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
    void Tridiag(int h, int N,  double* lambda_);
    void Similar(int N);

    int N;
    mat matr_A;
    mat sim;
};

#endif // MATRIX_H
