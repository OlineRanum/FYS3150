#include "prepare_results.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void Prepare_results::Prepare_results_2B(int number_of_tests, int* num_transform, double* Jacobi_t, double* arma_t)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("Results_2b.txt", fstream::out);
    myfile << "Testnumber" << setw(15) << " Transformation Number"<< setw(15) << "Jacobi" << setw(15) <<" Armadillo" << endl;
    for(int k = 0; k < number_of_tests; k++){
        myfile  << k+1 <<" & " << num_transform[k] << " & " << setprecision(8) << Jacobi_t[k] <<setw(15) << " & " << arma_t[k]<<setw(15)<< "\\\\ " <<  endl ;
    }
    myfile.close();

}
