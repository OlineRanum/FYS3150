#ifndef EXTERNAL_SOLVERS_H
#define EXTERNAL_SOLVERS_H

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

class External_Solvers
{
public:
    void eigen_solvers_arma(double* lambda_arma, int N_eigenvals, mat A_copy);

    int N;
    double a;
    double d;
    double tottime_arma;
    double tottime_jacobi;
    int max_k;
    int max_l;
    double off_A;
    double max_element;
private:
};

#endif // EXTERNAL_SOLVERS_H
