#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string>
#include <mpi.h>


#include "MonteCarloIntegration.h"
#include "GaussLaguerre.h"
#include "GaussLegendre.h"
#include "ReadFiles.h"
#include "WriteResults.h"

using namespace std;

int main()
{
    // Defining values
    int a = -3;
    int b = 3;

    // Defining instances and variables
    GaussLegendre *GLEG = new GaussLegendre();
    GaussLaguerre *GLAG = new GaussLaguerre();
    MonteCarloIntegration *MCI = new MonteCarloIntegration();
    ReadFiles *rf = new ReadFiles();
    WriteResults *wr = new WriteResults();
    vector<int> N;


    // Analytical result
    double exact_result = 5*M_PI*M_PI/256;
    printf("Exact result for alpha = 2: \t%.8f\t\n", exact_result);

    // Read N from file
    N = rf->Read_N_from_file();

    // Define pointers
    int number_of_tests = N.size();
    double * Gauss_Legendre = new double [number_of_tests];
    double * Gauss_Laguerre = new double [number_of_tests];
    double * mc = new double [number_of_tests];
    double * mc_var = new double [number_of_tests];
    int * N_Values = new int [number_of_tests];

    double * time_legendre = new double [number_of_tests];
    double * time_laguerre = new double [number_of_tests];
    double * time_mc = new double [number_of_tests];
    double * time_mc_importance = new double [number_of_tests];
    double * time_mc_parallellized = new double [number_of_tests];
    double alpha = 0.0;

    // Running Gauss_Legendre and writes a result file
    GLEG-> Init_GaussLegendre(N, Gauss_Legendre, N_Values, a, b, time_legendre);
    wr -> WR_2A(exact_result, Gauss_Legendre, number_of_tests, N_Values, time_legendre);

    // Running Gauss_Laguerre and writes a result file
    GLAG -> Init_GaussLaguerre(N, Gauss_Laguerre, N_Values, a, b, alpha, time_laguerre);
    wr -> WR_2B(exact_result, Gauss_Laguerre, number_of_tests, N_Values, time_laguerre);

    // Running brute force Monte Carlo Integration and writes a result file
    MCI -> Init_MonteCarloIntegration(N, mc, mc_var, N_Values, a, b, 0, 0, time_mc);
    wr-> MC_0(exact_result, mc, mc_var, number_of_tests, N_Values, time_mc);

    // Running Monte Carlo Integration with importance sampling and writes a result file
    MCI -> Init_MonteCarloIntegration(N, mc, mc_var, N_Values, a, b, 1, 0, time_mc_importance);
    wr-> MC_1(exact_result, mc, mc_var, number_of_tests, N_Values, time_mc_importance);

   // Running parallellized Monte Carlo Integration with importance sampling and writes a result file
    MPI_Init(NULL, NULL);
    MCI -> Init_MonteCarloIntegration(N, mc, mc_var, N_Values, a, b, 2, 0, time_mc_parallellized);
    MPI_Finalize ();
    wr-> MC_2(exact_result, mc, mc_var, number_of_tests, N_Values, time_mc_parallellized);


    return 0;
}
