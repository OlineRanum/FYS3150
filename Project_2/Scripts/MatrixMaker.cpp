#include <iostream>
#include <cmath>
#include <armadillo>
#include "MatrixMaker.h"
#include <iomanip>
using namespace std;
using namespace arma;

extern mat A;
extern mat A_copy;

void MatrixMaker::Tridiag(double h, int N,  double* lambda_analytical )
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    A = mat(N,N, fill::zeros);
    for (int k = 0; k < N; k++) A(k, k) = d;
    for (int k = 0; k < N-1; k++) A(k, k+1) = a;
    for (int k = 1; k < N; k++) A(k, k-1) = a;

    A_copy = A;
}
