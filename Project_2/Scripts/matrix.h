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
    void find_max_index();

    int N;
    mat A;
    double a;
    double d;
    int max_k;
    int max_l;
    double off_A;
    double max_element;
private:
};

#endif // MATRIX_H
