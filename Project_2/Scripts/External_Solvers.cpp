#include "External_Solvers.h"

#include <iostream>
#include <cmath>
#include <armadillo>
#include <iomanip>
#include "MatrixMaker.h"

using namespace std;
using namespace arma;

extern mat A;
extern mat A_copy;


void External_Solvers::eigen_solvers_arma(double* lambda_arma, int N_eigenvals, mat A_copy) {
    // Solving matrix using armadillo eigensoler
    vec eigval;
    mat eigvec;
    clock_t st, fi;
    st = clock();
    eig_sym(eigval, eigvec, A_copy);
    fi = clock();
    tottime_arma = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
}
