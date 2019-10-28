#include "WriteResults.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string.h>

using namespace arma;

using namespace std;

void WriteResults::WR_2B(int N_length, double* N, double* E, double* E2, double* M, double* M2, double* Abs_M, double* Chi, double* CV)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_4B.txt", fstream::out);
    myfile << "N" << setw(15) << "E" << setw(15) << "E2"<< setw(15) << "M"<< setw(15) << "M2" << setw(15) << "Abs_M"<< setw(15) << "CV" << setw(15) << "Chi"<<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_length; k++){
        myfile  << N[k] << setw(15) << E[k] << setw(15)<< E2[k] << setw(15) << M[k] << setw(15) << M2[k]<< setw(15) << Abs_M[k] << setw(15) << CV[k] << setw(15) << Chi[k]<< endl;
    }
    myfile.close();
}
