#ifndef PREPARE_RESULTS_H
#define PREPARE_RESULTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string.h>

using namespace arma;
using namespace std;

class PrepareResults
{
public:
    void Prepare_results_2B(int number_of_tests, int* num_transform, double* Jacobi_t, double* arma_t);
    void Prepare_results_2B_eigenvalues(int N, double* lambda_jacobi, double* lambda_analytical);
    void Prepare_results_2D(int number_of_tests, int N, double* lambda_jacobi, string filecode);
    void Prepare_results_2E(int number_of_tests, int N,  double* lambda_jacobi, string omega_value, string index);
    void Prepare_results_2F_egienvectors(int N,  mat I, double* lambda_jacobi_2e);

};

#endif // PREPARE_RESULTS_H
