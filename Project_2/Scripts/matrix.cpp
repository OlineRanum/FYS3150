#include <iostream>
#include <cmath>
#include <armadillo>
#include "matrix.h"
using namespace std;
using namespace arma;

void Matrix::Tridiag(double h, int N,  double* lambda_)
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);

    cout << "d: " << d << "  a: " << a << endl;

    matr_A = mat(N,N, fill::zeros);
    for (int k = 0; k < N; k++) matr_A(k, k) = d;
    for (int k = 0; k < N-1; k++) matr_A(k, k+1) = a;
    for (int k = 1; k < N; k++) matr_A(k, k-1) = a;

    for (int k = 0; k < N; k++) lambda_[k] = d+2*a*cos((k+1)*M_PI/(N+1));
    for (int k = 0; k < N; k++) cout << "lambda_1: " <<lambda_[k] <<  endl;
}

void Matrix::Similar(int N, double k, double l, double s, double c) {
    sim = mat(N,N, fill::zeros);
    for (int i = 0;  i< N; i++) sim(i, i) = 1;

    sim(k,l) = s;
    sim(l,k) = s;
    sim(k,k) = c;
    sim(l,l) = c;
 //   cout << sim << endl;
}


void Matrix::Jacobi(int N) {
    double off_A = 1;
    double max_element = matr_A(N/2+1, N/2);
    double max_k = N/2+1;
    double max_l= N/2;
    double tau;
    double t1;
    double t2;
    double t;
    double s;
    double c;

    mat matr_new_A = matr_A;
    mat matr_B = matr_A;
    int iteration_counter = 0;

    while (off_A > 1e-5) {

        iteration_counter += 1;

        if (iteration_counter == 1)
            {matr_new_A = matr_A;}

        else
            {matr_new_A = matr_B;
           // matr_B.zeros();
        }

        cout << "iteration counter: " << iteration_counter << endl;
        cout << matr_new_A << endl;

        max_element = 0;//matr_new_A(N/2+1, N/2);

        off_A = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if  (i!=j){
                    if ((abs(matr_new_A(i, j)) > max_element) && (matr_new_A(i, j) !=0)) {
                    max_k = i;
                    max_l = j;
                    max_element = abs(matr_new_A(i, j));
                    }
                off_A += matr_new_A(i, j)*matr_new_A(i, j);
                }

            }
        }
        cout << "k: " << max_k << "    l: " << max_l << "     max_element: " << max_element << endl;

        tau = (matr_new_A(max_l,max_l) - matr_new_A(max_k,max_k))/(2*matr_new_A(max_k,max_l));
        t1 = -tau + sqrt(1+tau*tau);
        t2 = -tau - sqrt(1+tau*tau);
        t = min(abs(t1),abs(t2));
        c = 1/sqrt(1+t*t);
        s = t*c;
        cout << "c: "<< c << "    s: " << s << endl;

//        Similar(N, max_k, max_l, s, c);


        matr_B(max_k,max_k) = matr_new_A(max_k,max_k)*c*c-2*matr_new_A(max_k,max_l)*c*s+matr_new_A(max_l,max_l)*s*s;
        matr_B(max_l,max_l) = matr_new_A(max_l,max_l)*c*c+2*matr_new_A(max_k,max_l)*c*s+matr_new_A(max_k, max_k)*s*s;
        matr_B(max_k, max_l) = matr_B(max_l, max_k) = 0;//(matr_new_A(max_k, max_k) -matr_new_A(max_l, max_l) )*c*s+matr_new_A(max_k, max_l)*(c*c-s*s);

        for (int i = 0; i < N; i++) {
                   if ((i != max_k) && (i != max_l)){  //  cout <<"h: " << h <<endl;
                matr_B(i,i) = matr_new_A(i,i);
                matr_B(i,max_k) = matr_B(max_k,i) = matr_new_A(i,max_k)*c-matr_new_A(i,max_l)*s;
                matr_B(i,max_l) = matr_B(max_l,i) = matr_new_A(i,max_l)*c+matr_new_A(i,max_k)*s;
                }}
        off_A = sqrt(off_A);
        //cout << matr_B <<endl;
        cout << "off_A:  " << off_A << endl;
    }

}
