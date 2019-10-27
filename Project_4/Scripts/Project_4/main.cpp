#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string>

#include "ReadFiles.h"
#include "PrepareSystem.h"
#include "Metropolis.h"
#include "ExpectationValues.h"

using namespace std;
using namespace arma;

int main()
{
    // ISING MODEL
    ReadFiles *rf = new ReadFiles();
    PrepareSystem *mtrx = new PrepareSystem();
    Metropolis *met = new Metropolis();
    ExpectationValues *expval = new ExpectationValues();
    vector<int> L, T, N;

    int J = 1;
    int k_b = 1;

    // Read Variables from file
    L = rf->Read_L_from_file();
    T = rf->Read_T_from_file();
    N = rf->Read_N_from_file();
    int n = N[0];
    double * Energy_values = new double [n];
    double * Magnetization = new double [n];
    double * Expectation_Values = new double [7];

    cout << "L: " << L[0] << endl << "T: " << T[0] << endl << "N: " << N[0] << endl;

    mtrx-> PrepareSpinMatrix(L[0]);
    met -> Metropolis_Method(mtrx->SpinSystem, L[0], T[0], N[0], Energy_values, Magnetization);
    expval -> Estimate_ExpectationValues(Energy_values, Magnetization, n, T[0], Expectation_Values);

    cout << "<E>      = " << Expectation_Values[0] << endl;
    cout << "<E2>     = " << Expectation_Values[1] << endl;
    cout << "<M>      = " << Expectation_Values[2] << endl;
    cout << "<M2>     = " << Expectation_Values[3] << endl;
    cout << "<abs(M)> = " << Expectation_Values[4] << endl;
    cout << "C_V      = " << Expectation_Values[5] << endl;
    cout << "CHI      = " << Expectation_Values[6] << endl;


    for (int i = 0; i < N[0]; i++) {
        cout <<i << " E: " << Energy_values[i] << " M: " << Magnetization[i] << endl;
    }

}
