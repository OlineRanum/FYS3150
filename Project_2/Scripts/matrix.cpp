#include "matrix.h"

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

void Tridiag(int h, int N,  double* lambda_)
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    for (int k = 0; k < N; k++) lambda_[k] = d+2*a*cos(k*M_PI/(N+1));

    mat matr_A(N,N, fill::zeros);
    for (int k = 0; k < N-1; k++) matr_A(k, k) = d;
    for (int k = 0; k < N-1; k++) matr_A(k, k+1) = a;
    for (int k = 1; k < N; k++) matr_A(k, k-1) = a;
}

void Similar(int N) {
    mat sim(N,N, fill::zeros);
    for (int k = 0; k < N; k++) sim(k, k) = 1;

    int l= 2;
    int k = 6;
    double s = 3;
    double c = 4;

    sim(k,l) = s;
    sim(l,k) = s;
    sim(k,k) = c;
    sim(l,l) = c;
}
