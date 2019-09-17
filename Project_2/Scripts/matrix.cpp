#include <iostream>
#include <cmath>
#include <armadillo>
#include "matrix.h"
#include <iomanip>
using namespace std;
using namespace arma;

void Matrix::Tridiag(double h, int N,  double* lambda_analytical )
{
    double d = 2/(double)(h*h);
    double a = -1/(double)(h*h);


    A = mat(N,N, fill::zeros);
    for (int k = 0; k < N; k++) A(k, k) = d;
    for (int k = 0; k < N-1; k++) A(k, k+1) = a;
    for (int k = 1; k < N; k++) A(k, k-1) = a;

  //  for (int k = 0; k < N; k++) lambda_analytical[k] += d+2*a*cos((k+1)*M_PI/(N+1));
 //   cout << "Analytical eigenvalues:" << endl;
  //  for (int k = 0; k < N; k++) cout << "lambda " << k <<" " <<lambda_[k] <<  endl;
   // cout << "_______________________________" << endl << endl ;
    A_copy = A;
}

void Matrix::eigen_solvers(double* lambda_arma, int N_eigenvals) {
    // Solbing matrix using armadillo eigensoler
    vec eigval;
    mat eigvec;
    clock_t st, fi;
    st = clock();
    eig_sym(eigval, eigvec, A_copy);
    fi = clock();
    tottime_arma = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
 //   cout << "Armadillo eigenvalues: "<< endl;
  //  cout << eigval << endl;
//    for (int k = 0; k < N_eigenvals; k++) lambda_arma[k] = eigval[k];
    //for (int k = 0; k < N_eigenvals; k++) cout << lambda_arma[k];
}


void Matrix::find_max_index() {
    max_element = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if  (i!=j){
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

void Matrix::Jacobi(int N, double* Jacobi_t, double* arma_t, int number_of_tests, int* num_transform, double* lambda_jacobi) {
    this->N = N;
    off_A = 1;
    max_k = 0; max_l= 0;
    double tau;
    double t1; double t2; double t;
    double s; double c;
    double BKK; double BLL; double BKL;

    int sinmilarity_transform_counter = 0;

//    cout << "Initial matrix" << endl << endl;
//    cout << A << endl;

    clock_t st, fi;
    st = clock();
    while (off_A > 1e-10) {
        sinmilarity_transform_counter += 1;
        off_A = 0;

        find_max_index();

        tau = (A(max_l,max_l) - A(max_k,max_k))/(2*A(max_k,max_l));
        t1 = -tau + sqrt(1+tau*tau);
        t2 = -tau - sqrt(1+tau*tau);
        if (abs(t1) > abs(t2)) {t = t2;} else {t = t1;}
        c = 1/sqrt(1+t*t);
        s = t*c;

        /*
        cout << "k: " << max_k << "    l: " << max_l << "     max_element: " << max_element << endl;
        cout << "iteration counter: " << sinmilarity_transform_counter << endl;
        cout << A << endl;
        cout << "c: "<< c << "    s: " << s << endl;
        cout << "off_A:  " << off_A << endl;
        cout << "_____________________________________________________________" << endl;
        */

        BKK = A(max_k,max_k)*c*c-2*A(max_k,max_l)*c*s+A(max_l,max_l)*s*s;
        BLL = A(max_l,max_l)*c*c+2*A(max_k,max_l)*c*s+A(max_k, max_k)*s*s;
        BKL = 0; //(A(max_k, max_k) -A(max_l, max_l) )*c*s+A(max_k, max_l)*(c*c-s*s);


        for (int i = 0; i < N; i++) {
            if ((i != max_k) && (i != max_l)){  //  cout <<"h: " << h <<endl;
                double AIK = A(i,max_k)*c-A(i,max_l)*s;
                double AIL = A(i,max_l)*c+A(i,max_k)*s;
                A(i,i) = A(i,i);
                A(i,max_k) = A(max_k,i) = AIK;
                A(i,max_l) = A(max_l,i) = AIL;
                }}


        A(max_k,max_k) = BKK;
        A(max_l,max_l) = BLL;
        A(max_k, max_l) = A(max_l, max_k) = BKL;

        off_A = sqrt(off_A);

        }
    fi = clock();
    tottime_jacobi = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );

//    cout << "Final stage matrix: " << endl << endl;
    cout << A << endl;
    cout << "Time of Jacobi solver= " << tottime_jacobi << endl;
    cout << "Time of Armadillo solver= " << tottime_arma << endl;
//    for (int k = 0; k < N; k++) lambda_jacobi[k] = A(k,k);

    Jacobi_t[number_of_tests-1] = tottime_jacobi;
    arma_t[number_of_tests-1] = tottime_arma;
    num_transform[number_of_tests-1] = sinmilarity_transform_counter;
}
