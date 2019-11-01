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
    myfile.open ("../../Py_Scripts/Results/4B/R_4B.txt", fstream::out);
    myfile << "N" << setw(15) << "E" << setw(15) << "E2"<< setw(15) << "M"<< setw(15) << "M2" << setw(15) << "Abs_M"<< setw(15) << "CV" << setw(15) << "Chi"<<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_length; k++){
        cout << E[k] << endl;
        myfile  << N[k] << setw(15) << E[k] << setw(15)<< E2[k] << setw(15) << M[k] << setw(15) << M2[k]<< setw(15) << Abs_M[k] << setw(15) << CV[k] << setw(15) << Chi[k]<< endl;
    }
    myfile.close();
}


void WriteResults::WR_2C(int Frac_length, double* E,double* Abs_M, double* N_cycles, int it_counter, double* AC)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Py_Scripts/Results/4C/R_4C_O_24T_" + to_string(it_counter) +".txt", fstream::out);
    myfile << "N" << setw(15) << "E" << setw(15)  << "Abs_M"<< setw(15) << "Accepted Cycles" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < Frac_length; k++){
        myfile  << N_cycles[k] << setw(15) << E[k] << setw(15)<< Abs_M[k] << setw(15)<< AC[k] << endl;
    }
    myfile.close();
    cout << "PRINTPRINT" << endl;
}

void WriteResults::WR_2D(double* E, int N_mc, int it_counter, int L) {
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Py_Scripts/Results/4D/4D_R_1T_" + to_string(it_counter) +".txt", fstream::out);
    myfile << "N" << setw(15) << "E" <<endl;
    myfile << "------------------------------------" << endl;
    int BurnIn = 5000;
    for (int k = BurnIn; k < N_mc; k++){
        if (k % 100 == 0) {
        myfile  << k << setw(15) << E[k]/(L*L) << endl; }
    }
    myfile.close();
    cout << "PRINTPRINT" << endl;
}


void WriteResults::WR_2E(int T_length, double* T, double* E, double* E2, double* M, double* M2, double* Abs_M, double* Chi, double* CV, int L, int it_counter)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Py_Scripts/Results/4E/WrittenFiles/L_"+ to_string(L)+ "_"+to_string(it_counter) +".txt", fstream::out);
    myfile << "T" << setw(15) << "E" << setw(15) << "E2"<< setw(15) << "M"<< setw(15) << "M2" << setw(15) << "Abs_M"<< setw(15) << "CV" << setw(15) << "Chi"<<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < T_length; k++){
        cout  << T[k] << setw(15) << E[k] << setw(15)<< E2[k] << setw(15) << M[k] << setw(15) << M2[k]<< setw(15) << Abs_M[k] << setw(15) << CV[k] << setw(15) << Chi[k]<< endl;
        myfile  << T[k] << setw(15) << E[k] << setw(15)<< E2[k] << setw(15) << M[k] << setw(15) << M2[k]<< setw(15) << Abs_M[k] << setw(15) << CV[k] << setw(15) << Chi[k]<< endl;
    }
    myfile.close();
}
