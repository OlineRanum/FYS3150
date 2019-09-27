#include "PrepareResults.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string.h> 

using namespace arma;

using namespace std;

void PrepareResults::Prepare_results_2B(int number_of_tests, int* num_transform, double* Jacobi_t, double* arma_t)
{
    // Writing values to text file with latex friendly format
    fstream myfile;

    myfile.open ("Results_2b.txt", fstream::out);
    char string_1[50] = "Testnumber";
    char string_2[50] = "Transformation Number";
    char string_3[50] = "Jacobi";
    char string_4[50] = "Armadillo";
    //double sum_of_jac = 0;
    myfile << string_1 << setw(15) << string_2 << setw(15) << string_3 << setw(15) << string_4 << endl;
    for (int k = 0; k < number_of_tests; k++){
        myfile  << setw((strlen(string_1)/2)) << k+1 << setw((strlen(string_1)/2)+(strlen(string_2)/2)) <<"& " << num_transform[k] << 
        setw((strlen(string_2)/2)+(strlen(string_3)/2)+5) <<"& " << setprecision(8) << Jacobi_t[k] << setw((strlen(string_3)/2)+
        (strlen(string_4)/2))<< "& " << arma_t[k]<<setw(15)<< "\n";
        //sum_of_jac += Jacobi_t[k];
        }
    //myfile << "Average Jacobi: " << sum_of_jac/10 << endl;
    myfile.close();
}

void PrepareResults::Prepare_results_2B_eigenvalues(int N, double* lambda_jacobi, double* lambda_analytical)
{
    vec lambda_(N);
    for (int k = 0; k < N; k++) {lambda_(k) = lambda_jacobi[k];}
    vec lambda_sorted = sort(lambda_);

    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("Results_2b_lambda.txt", fstream::out);
    myfile << "# " << setw(10)<< "       Lambda Analytical    "<< setw(20) << "Lambda Jacobi" << endl;
    for(int k = 0; k < N; k++){
        myfile  << k+1 <<setw(10) << " & " << setprecision(15)<< lambda_sorted(k) << "      & " << lambda_analytical[k] << endl ;
    }
    myfile.close();

}


void PrepareResults::Prepare_results_2D(int number_of_tests, int N,  double* lambda_jacobi, string filecode)
{
    vec lambda_(N);
    for (int k = 0; k < N; k++) {lambda_(k) = lambda_jacobi[k];}
    //for (int k = 0; k < N; k++) cout << lambda_(k)<< endl;
    vec lambda_sorted = sort(lambda_);


    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("Results_2D" + filecode + ".txt", fstream::out);
    myfile << "Testnumber" << setw(15) << "Lambda" << endl;
    for(int k = 0; k < N; k++){
        myfile  << k+1 <<" & " << lambda_sorted(k) <<  endl ;
    }
    myfile.close();
}


void PrepareResults::Prepare_results_2E(int number_of_tests, int N,  double* lambda_jacobi, string omega_value, string index)
{
    vec lambda_(N);
    for (int k = 0; k < N; k++) {lambda_(k) = lambda_jacobi[k];}
    vec lambda_sorted = sort(lambda_);

    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("Results_2E_" + omega_value + +"_"+index+"_"+"_.txt", fstream::out);
    myfile << "Testnumber" << setw(15) << "Lambda" << endl;
    for(int k = 0; k < N; k++){
        myfile  << k+1 <<" &        " << setprecision(15)<< lambda_sorted(k) <<  endl ;
    }
    myfile.close();
}

void PrepareResults::Prepare_results_2F_egienvectors(int N,  mat I, double* lambda_jacobi_2e)
{
    // Find index of minimum value
    int k;
    double min_val = lambda_jacobi_2e[0];
    for(int j = 0; j < N; j++){
        if (abs(lambda_jacobi_2e[j]) < min_val) {k = j; min_val = lambda_jacobi_2e[j];}
        cout << lambda_jacobi_2e[j] << endl;
    }

    cout << "Min value:" << k << endl;
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("Results_2F_eigenvectors.txt", fstream::out);
    for(int k = 0; k < N; k++){
        for (int j = 0; j < N; j++){
        myfile  << " " << I(k,j) <<"";
}    myfile << endl;}
    myfile.close();

    myfile.open ("Results_2F_eigenvectors_info.txt", fstream::out);
    myfile << "ground_state index: " << k << endl;
    myfile << "N: " << N << endl;
    myfile << "Testnumber" << setw(15) << "Lambda" << endl;
    myfile << endl;
    myfile.close();


}
