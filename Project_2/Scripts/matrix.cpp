#include <iostream>
#include <cmath>
#include <armadillo>
#include "matrix.h"
using namespace std;
using namespace arma;

void Matrix::Tridiag(double h, int N,  double* lambda_)
{
    cout <<"h: " << h <<endl;
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);
    cout << "d: " << d << "  a: " << a << endl;

    for (int k = 0; k < N; k++) lambda_[k] = d+2*a*cos(k*M_PI/(N+1));

    matr_A = mat(N,N, fill::zeros);
    for (int k = 0; k < N-1; k++) matr_A(k, k) = d;
    for (int k = 0; k < N-1; k++) matr_A(k, k+1) = a;
    for (int k = 1; k < N; k++) matr_A(k, k-1) = a;
 //   cout << matr_A << endl;
}

void Matrix::Similar(int N, double k, double l, double s, double c) {
    sim = mat(N,N, fill::zeros);
    for (int i = 0;  i< N; i++) sim(i, i) = 1;

    sim(k,l) = s;
    sim(l,k) = s;
    sim(k,k) = c;
    sim(l,l) = c;
    cout << sim << endl;
}


void Matrix::Jacobi(int N) {
    double off_A = 1;
    double max_element = matr_A(N/2+1, N/2);
    cout << max_element;
    double max_k = N/2+1;
    double max_l= N/2;

    mat matr_B(N,N, arma::fill::zeros);

    while (off_A > 0.5) {
        off_A = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if  (i!=j){
                    if ((matr_A(i, j) > max_element) && (matr_A(i, j) !=0)) {
                    max_k = i;
                    max_l = j;
                    max_element = matr_A(i, j);
                    cout << "max_element" << max_element << endl;
                    }
                off_A += matr_A(i, j)*matr_A(i, j);
                if (matr_A(i, j)*matr_A(i, j) != 0) {
                }
                }

            }
        }
        double tau = (matr_A(max_l,max_l) - matr_A(max_k,max_k))/(2*matr_A(max_k,max_l));
        double t1 = -tau + sqrt(1+tau*tau);
        double t2 = -tau - sqrt(1+tau*tau);
        double t = min(abs(t1),abs(t2));
        double c = 1/(sqrt(1+abs(t*t)));
        double s = t*c;
        cout << "c: "<< max_k << "    s: " << max_l << endl;

        Similar(N, max_k, max_l, s, c);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((i != max_k) && (i != max_l)){
                matr_B(i,i) = matr_A(i,i);
                matr_B(i,max_k) = matr_A(i,max_k)*c-matr_A(i,max_l)*s;
                matr_B(i,max_l) = matr_A(i,max_l)*c+matr_A(i,max_k)*s;
                }
                matr_B(max_k,max_k) = matr_A(max_k,max_k)*c*c-2*matr_A(max_k,max_l)*c*s+matr_A(max_l,max_l)*s*s;
                matr_B(max_l,max_l) = matr_A(max_l,max_l)*c*c+2*matr_A(max_k,max_l)*c*s+matr_A(max_k, max_k)*s*s;
                matr_B(max_k, max_l) = (matr_A(max_k, max_k) -matr_A(max_l, max_l) )*c*s+matr_A(max_k, max_l)*(c*c-s*s);
           }}
        off_A = sqrt(off_A);
        off_A = 0.4;
        cout << matr_B <<endl;
        cout << "off_A:  " << off_A << endl;
    }

}
