#ifndef JACOBI_METHOD_H
#define JACOBI_METHOD_H
#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


class Jacobi_Method
{
public:
    void Jacobi(int N, double* Jacobi_t, double* arma_t, int number_of_tests, int* num_transform, double* lambda_jacobi, mat A, mat& I );
    void find_max_index(mat A);

    int N;
    mat A;
    mat I;
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

#endif // JACOBI_METHOD_H

