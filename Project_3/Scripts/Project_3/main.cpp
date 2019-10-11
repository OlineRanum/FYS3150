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
    double * mc_std = new double [number_of_tests];
    int * N_Values = new int [number_of_tests];


    GLEG-> Init_GaussLegendre(N, Gauss_Legendre, N_Values, a, b);
    wr -> WR_2A(exact_result, Gauss_Legendre, number_of_tests, N_Values);
/*
    double alpha = 0.0;
    GLAG -> Init_GaussLaguerre(N, Gauss_Laguerre, N_Values, a, b, alpha);
    wr -> WR_2B(exact_result, Gauss_Legendre, number_of_tests, N_Values);

    MCI -> Init_MonteCarloIntegration(N, mc, mc_std, N_Values, a, b, 1, 0);*/

    /*
    int numprocs; int my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    double time_start = MPI_Wtime();

    MCI -> Init_MonteCarloIntegration(N, mc, mc_std, N_Values, a, b, 2, my_rank);

    double local_sum; double total_sum;
    local_sum = *mc;

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double time_end = MPI_Wtime();

    double total_time = time_end-time_start;

    if ( my_rank == 0) {
      cout << "Local sum 0 = " <<  local_sum << endl;
      cout << "Parallelalized sum = " <<  total_sum/numprocs << endl;
      cout << "Time = " <<  total_time  << " on number of processors: "  << numprocs  << endl;
    }

    MPI_Finalize (); */
    // run as mpirun -n 4 ./Project_3 in terminal from release folder

    return 0;
}
