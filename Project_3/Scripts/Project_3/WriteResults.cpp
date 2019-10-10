#include "WriteResults.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string.h>

using namespace arma;

using namespace std;

void WriteResults::WR_2A(double analytical, double * G_legendre, int N_test, int * N_values)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_2A.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "G-Leguerre" << endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15) << G_legendre[k] << endl;
    }
    myfile.close();
}


