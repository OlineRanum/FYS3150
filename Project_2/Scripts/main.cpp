#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "ReadFiles.h"
#include "matrix.h"
#include "prepare_results.h"


using namespace std;

void test (int N, double h, double* lambda_);

int main()
{
    ReadFiles *rf = new ReadFiles();
    Prepare_results *pf = new Prepare_results();
    Matrix *mtrx = new Matrix();
    vector<int> v;
    v = rf->Read_N_from_file();

    int number_of_tests = 0;
    for (int z: v) number_of_tests +=1;

    double * Jacobi_t =  new double [number_of_tests];

    double * arma_t = new double [number_of_tests];

    int * num_transform = new int [number_of_tests];

//    double* eigenval_analytical;



    number_of_tests = 0;

    for (int z: v){
       int N = z;
       number_of_tests +=1;

       double * lambda_analytical = new double [N];
       double * lambda_jacobi = new double [N];
       double * lambda_arma = new double [N];

       double h = 1.0/(double)(N);

       mtrx->Tridiag(h,N,lambda_analytical);
       mtrx->eigen_solvers(lambda_arma, N);
       mtrx->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi);
    }



    cout << "Number of tests: " << number_of_tests << endl;

    pf ->Prepare_results_2B(number_of_tests, num_transform, Jacobi_t, arma_t);



    delete[] Jacobi_t;
    delete[] arma_t;

    return 0;
}
