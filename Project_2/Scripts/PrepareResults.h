#ifndef PREPARE_RESULTS_H
#define PREPARE_RESULTS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>

using namespace arma;

class PrepareResults
{
public:
    void Prepare_results_2B(int number_of_tests, int* num_transform, double* Jacobi_t, double* arma_t);
    void Prepare_results_2E(int number_of_tests, int N, double* lambda_jacobi);

};

#endif // PREPARE_RESULTS_H
