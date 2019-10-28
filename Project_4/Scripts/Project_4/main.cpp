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
#include "WriteResults.h"

using namespace std;
using namespace arma;

int main()
{
    // ISING MODEL
    ReadFiles *rf = new ReadFiles();
    WriteResults *wr = new WriteResults();
    PrepareSystem *mtrx = new PrepareSystem();
    Metropolis *met = new Metropolis();
    ExpectationValues *expval = new ExpectationValues();
    vector<int> L, T, N ;

    int J = 1;
    int k_b = 1;

    // Read Variables from file
    L = rf->Read_L_from_file();
    T = rf->Read_T_from_file();
    N = rf->Read_N_from_file();

    int N_length = 0;
    for (int n: N){N_length += 1;}

    double* n_vals = new double [N_length];
    double* ex_E = new double [N_length];
    double* ex_E2 = new double [N_length];
    double* ex_M = new double [N_length];
    double* ex_M2 = new double [N_length];
    double* ex_abs_M = new double [N_length];
    double* Chi = new double [N_length];
    double* CV = new double [N_length];

    int it_counter = 0;
    for (int n: N){
        double * Energy_values = new double [n];
        double * Magnetization = new double [n];
        double * Expectation_Values = new double [7];

        cout << "L: " << L[0] << endl << "T: " << T[0] << endl << "N: " << n << endl;

        mtrx-> PrepareSpinMatrix(L[0]);
        met -> Metropolis_Method(mtrx->SpinSystem, L[0], T[0], n , Energy_values, Magnetization);
        expval -> Estimate_ExpectationValues(Energy_values, Magnetization, n, T[0], Expectation_Values);

        cout << "<E>      = " << Expectation_Values[0] << endl;
        cout << "<E2>     = " << Expectation_Values[1] << endl;
        cout << "<M>      = " << Expectation_Values[2] << endl;
        cout << "<M2>     = " << Expectation_Values[3] << endl;
        cout << "<abs(M)> = " << Expectation_Values[4] << endl;
        cout << "C_V      = " << Expectation_Values[5] << endl;
        cout << "CHI      = " << Expectation_Values[6] << endl;

        n_vals[it_counter] = n;
        ex_E[it_counter] = Expectation_Values[0];
        ex_E2[it_counter] = Expectation_Values[1];
        ex_M[it_counter] = Expectation_Values[2];
        ex_M2[it_counter] = Expectation_Values[3];
        ex_abs_M[it_counter] = Expectation_Values[4];
        Chi[it_counter] = Expectation_Values[5];
        CV[it_counter] = Expectation_Values[6];

        it_counter +=1;
    }

  //  for (int i = 0; i < N[0]; i++) {
    //    cout <<i << " E: " << Energy_values[i] << " M: " << Magnetization[i] << endl;
    //}

    wr -> WR_2B(N_length, n_vals, ex_E, ex_E2, ex_M, ex_M2, ex_abs_M, Chi, CV);

    delete[] n_vals; delete [] ex_E; delete [] ex_E2; delete [] ex_M; delete [] ex_M2; delete [] ex_abs_M; delete [] Chi; delete [] CV;
}
