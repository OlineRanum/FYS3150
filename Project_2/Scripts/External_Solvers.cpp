#include "External_Solvers.h"

#include <iostream>
#include <cmath>
#include <armadillo>
#include <iomanip>
#include "MatrixMaker.h"

using namespace std;
using namespace arma;



void External_Solvers::eigen_solvers_arma(double* lambda_arma, int N_eigenvals, mat A_copy, double* arma_t, int number_of_tests) {
    // Solving matrix using armadillo eigensoler
    vec eigval;
    mat eigvec;
    clock_t st, fi;
    st = clock(); 
    eig_sym(eigval, eigvec, A_copy);

    for (int x = 0; x < N_eigenvals; x++){lambda_arma[x] = eigval(x);}
    fi = clock();
    tottime_arma = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    arma_t[number_of_tests-1] = tottime_arma;

}
