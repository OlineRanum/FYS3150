#include <iostream>
#include <cmath>
#include <armadillo>
#include "MatrixMaker.h"
#include <iomanip>
using namespace std;
using namespace arma;


void MatrixMaker::Tridiag(double h, int N,  double* lambda_analytical )
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    A = mat(N,N, fill::zeros);
    for (int k = 0; k < N; k++) A(k, k) = d;
    for (int k = 0; k < N-1; k++) A(k, k+1) = a;
    for (int k = 1; k < N; k++) A(k, k-1) = a;

    for (int k = 0; k < N; k++) lambda_analytical[k] = d+2*a*cos((k+1)*M_PI/(N+1));
    for (int k = 0; k < N; k++) cout << lambda_analytical[k] << endl;

    A_copy = A;
}


void MatrixMaker::Tridiag_QD1e(double h, int N, double* rho)
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    A_q = mat(N,N, fill::zeros);
    for (int k = 0; k < N; k++) A_q(k, k) = d + rho[k]*rho[k];
    for (int k = 0; k < N-1; k++) A_q(k, k+1) = a;
    for (int k = 1; k < N; k++) A_q(k, k-1) = a;
}
