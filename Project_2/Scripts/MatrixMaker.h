#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


class MatrixMaker
{
public:
    void Tridiag(double h, int N,  double* lambda_analytical);
    void Jacobi(int N, double* Jacobi_t, double* arma_t, int number_of_tests, int* num_transform, double* lambda_jacobi);
    void find_max_index();
    void eigen_solvers(double* lambda_arma, int N_eigenvals);

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

#endif // MATRIX_H
