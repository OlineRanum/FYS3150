#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string>

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
    GaussLegendre *GL = new GaussLegendre();
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
    int * N_Values = new int [number_of_tests];

    GL-> Init_GaussLegendre(N, Gauss_Legendre, N_Values, a, b);

    wr -> WR_2A(exact_result, Gauss_Legendre, number_of_tests, N_Values);


}
