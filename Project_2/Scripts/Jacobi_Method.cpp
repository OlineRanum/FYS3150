#include "Jacobi_Method.h"

#include <iostream>
#include <cmath>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

void Jacobi_Method::find_max_index(mat A) {
    max_element = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if  (i!=j) {
                if (abs(A(i, j)) > max_element) {
                max_k = i;
                max_l = j;
                max_element = abs(A(i, j));
                }
            off_A += A(i, j)*A(i, j);
            }
        }
    }
}

void Jacobi_Method::Jacobi(int N, double* Jacobi_t, double* arma_t, int number_of_tests, int* num_transform, double* lambda_jacobi, mat A) {
    this->N = N;
    off_A = 1;
    max_k = 0; max_l= 0;

    int sinmilarity_transform_counter = 0;

    clock_t st, fi;
    st = clock();
    while (off_A > 1e-10) {

        sinmilarity_transform_counter += 1;
        off_A = 0;

        find_max_index(A);


        double tau = (A(max_l,max_l) - A(max_k,max_k))/(2*A(max_k,max_l));

        double t1 = -tau + sqrt(1+tau*tau);
        double t2 = -tau - sqrt(1+tau*tau);
        double t;
        if (abs(t1) > abs(t2)) {t = t2;} else {t = t1;}
        double c = 1/sqrt(1+t*t);
        double s = t*c;

        double BKK = A(max_k,max_k)*c*c-2*A(max_k,max_l)*c*s+A(max_l,max_l)*s*s;
        double BLL = A(max_l,max_l)*c*c+2*A(max_k,max_l)*c*s+A(max_k, max_k)*s*s;
        double BKL = 0; //(A(max_k, max_k) -A(max_l, max_l) )*c*s+A(max_k, max_l)*(c*c-s*s);


        for (int i = 0; i < N; i++) {
            if ((i != max_k) && (i != max_l)){  //  cout <<"h: " << h <<endl;
                double AIK = A(i,max_k)*c-A(i,max_l)*s;
                double AIL = A(i,max_l)*c+A(i,max_k)*s;
                A(i,i) = A(i,i);
                A(i,max_k) = A(max_k,i) = AIK;
                A(i,max_l) = A(max_l,i) = AIL;
                }
        }


        A(max_k,max_k) = BKK;
        A(max_l,max_l) = BLL;
        A(max_k, max_l) = A(max_l, max_k) = BKL;

        off_A = sqrt(off_A);
        cout << off_A << endl;
        }
    fi = clock();
    tottime_jacobi = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    for (int k = 0; k < N; k++) {lambda_jacobi[k] = A(k,k);}

 //   cout << A << endl;
    cout << "Time of Jacobi solver= " << tottime_jacobi << endl;
   // cout << "Time of Armadillo solver= " << tottime_arma << endl;
    cout <<"Final: "<< A << endl;
    Jacobi_t[number_of_tests-1] = tottime_jacobi;
 //   arma_t[number_of_tests-1] = tottime_arma;
    num_transform[number_of_tests-1] = sinmilarity_transform_counter;

}
