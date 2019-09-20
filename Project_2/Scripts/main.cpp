#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "ReadFiles.h"
#include "MatrixMaker.h"
#include "PrepareResults.h"
#include "Jacobi_Method.h"
#include "External_Solvers.h"
#include "tests.h"

using namespace std;


int main()
{
    ReadFiles *rf = new ReadFiles();
    PrepareResults *pf = new PrepareResults();
    MatrixMaker *mtrx = new MatrixMaker();
    Jacobi_Method *jack_meth = new Jacobi_Method();
    External_Solvers *ext_solv = new External_Solvers();
    vector<int> v;
    v = rf->Read_N_from_file();


    int number_of_tests = 0;
    for (int z: v) number_of_tests +=1;

    double * Jacobi_t =  new double [number_of_tests];
    double * arma_t = new double [number_of_tests];
    int * num_transform = new int [number_of_tests];

    double p_N = 2;
    double p_0 = 0;

    number_of_tests = 0;
    for (int z: v){
       int N = z;
       number_of_tests +=1;

       double * lambda_analytical = new double [N];
       double * lambda_jacobi = new double [N];
       double * lambda_jacobi_2E = new double [N];
       double * lambda_arma = new double [N];
       double * rho = new double [N];

       // Defining H
       double h = (p_N-p_0)/(double)(N+1);

       // Defining RHO
       for (int k = 0; k < N; k++) rho[k] = (k+1)*h;

       // Calculating stuff
       mtrx->Tridiag(h,N,lambda_analytical);
       mtrx->Tridiag_QD1e(h, N, rho);
       ext_solv->eigen_solvers_arma(lambda_arma, N, mtrx->A_copy);

       jack_meth->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi, mtrx->A);
       jack_meth->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi_2E, mtrx->A_q);

       pf -> Prepare_results_2E(number_of_tests, N, lambda_jacobi_2E);
    }



    cout << "Number of tests: " << number_of_tests << endl;

   // pf ->Prepare_results_2B(number_of_tests, num_transform, Jacobi_t, arma_t);



    delete[] Jacobi_t;
    delete[] arma_t;

    return 0;
}
