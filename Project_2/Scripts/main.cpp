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
    // Prepare clases
    ReadFiles *rf = new ReadFiles();
    PrepareResults *pf = new PrepareResults();
    MatrixMaker *mtrx = new MatrixMaker();
    Jacobi_Method *jacobi_method = new Jacobi_Method();
    External_Solvers *external_solvers = new External_Solvers();
    vector<int> v;
    v = rf->Read_N_from_file();

    // Prepare variables
    int number_of_tests = 0; for (int z: v) number_of_tests +=1;
    double * Jacobi_t =  new double [number_of_tests];
    double * arma_t = new double [number_of_tests];
    int * num_transform = new int [number_of_tests];
    int * N_of_test = new int [number_of_tests];
    double p_N = 1e6; double p_0 = 0;


    // Evaluate z files in N.txt
    number_of_tests = 0;
    for (int z: v){
       int N = z;
       N_of_test[number_of_tests] = N;
       number_of_tests +=1;


       double * lambda_analytical = new double [N];
       double * lambda_jacobi = new double [N];
       double * lambda_jacobi_2E = new double [N];
       double * lambda_arma = new double [N];
       double * rho = new double [N];

       // Defining h
       double h = (p_N-p_0)/(double)(N+1);

       // Defining Rho
       for (int k = 0; k < N; k++) rho[k] = (k+1)*h;

       // Setting up tridiagonal matrix
       mtrx->Tridiag(h,N,lambda_analytical);

       // Solve with armadillo
       external_solvers->eigen_solvers_arma(lambda_arma, N, mtrx->A_copy);

       // Solve with Jacobi Matrix
       jacobi_method->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi, mtrx->A);


       // Setting up tridiagonalmatrix with potential V
       mtrx->Tridiag_QD1e(h, N, rho);

       //Solving with Jacobi Matrix on potential
       jacobi_method->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi_2E, mtrx->A_q);


       // Prepareing results for 2D
       pf -> Prepare_results_2D(number_of_tests, N, lambda_jacobi_2E);

       pf -> Prepare_results_2B_eigenvalues(N, lambda_jacobi, lambda_analytical);


    delete[] lambda_analytical; delete[] lambda_jacobi; delete[] lambda_jacobi_2E; delete[] rho; delete[] lambda_arma;
    }



    cout << "Number of tests: " << number_of_tests << endl;

   pf -> Prepare_results_2B(number_of_tests, num_transform, Jacobi_t, arma_t);



    delete[] Jacobi_t;
    delete[] arma_t;
    return 0;
}
