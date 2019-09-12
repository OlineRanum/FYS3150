#include <iostream>
#include <cmath>
#include <armadillo>
#include "matrix.h"
using namespace std;
using namespace arma;

void Matrix::Tridiag(double h, int N,  double* lambda_)
{
    cout << h <<endl;
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    for (int k = 0; k < N; k++) lambda_[k] = d+2*a*cos(k*M_PI/(N+1));

    mat matr_A(N,N, fill::zeros);
    for (int k = 0; k < N-1; k++) matr_A(k, k) = d;
    for (int k = 0; k < N-1; k++) matr_A(k, k+1) = a;
    for (int k = 1; k < N; k++) matr_A(k, k-1) = a;
    cout << d;
}

void Matrix::Similar(int N) {
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


void Matrix::Jacobi() {
    double off_A = 1;
    double max_element = 0;
    double max_k = 0;
    double max_l= 0;
    while (off_A > 0.5) {
        off_A = 0;
        cout << "HER" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matr_A(i, j) > max_element) {
                    max_k = i;
                    max_l = j;
                    max_element = matr_A(i, j);
                if (i != j) {
                    off_A += matr_A(i, j)*matr_A(i, j);
                }
                }
            }
        }
        off_A = sqrt(off_A);
        cout << off_A << endl;
    }

}
