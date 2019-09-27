#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string>

#include "ReadFiles.h"
#include "MatrixMaker.h"
#include "PrepareResults.h"
#include "Jacobi_Method.h"
#include "External_Solvers.h"
#include "tests.h"
#include "n_text_timer.h"

using namespace std;
using namespace arma;

int main()
{
    // Comment these out if you don't want 10 times the values in N.txt
    N_Text_Timer * ntimes = new N_Text_Timer();
    ntimes->Timer();
    // Prepare clases
    ReadFiles *rf = new ReadFiles();
    PrepareResults *pf = new PrepareResults();
    MatrixMaker *mtrx = new MatrixMaker();
    Jacobi_Method *jacobi_method = new Jacobi_Method();
    External_Solvers *external_solvers = new External_Solvers();
    Tests * test = new Tests();
    vector<int> v;
    vector<int> rhoValues;
    v = rf->Read_N_from_file();
    rhoValues = rf->Read_rho_from_file();

    // Prepare variables
    int number_of_tests     = 0; for (int z: v) number_of_tests +=1;
    double  * Jacobi_t      =  new double [number_of_tests];
    double  * arma_t        = new double [number_of_tests];
    int     * num_transform = new int [number_of_tests];
    int     * N_of_test     = new int [number_of_tests];
                     //double p_N = 1;

    test->Test_max_non_diag_value();
    test->Test_eigenvalues();

    // Evaluate z files in N.txt
    number_of_tests = 0;
    for (int z: v){
    for (int y: rhoValues){
        cout << z<< " " <<y << endl;
       int N = z;
       double p_N = y; double p_0 = 0;

       N_of_test[number_of_tests] = N;
       number_of_tests +=1;

       double * lambda_analytical = new double [N];
       double * lambda_jacobi = new double [N];
       double * lambda_jacobi_2E = new double [N];
       double * lambda_jacobi_E = new double [N];
       double * lambda_arma = new double [N];
       double * rho = new double [N];

       // Defining h
       double h = (p_N-p_0)/(double)(N+1);

       // Defining Rho
       for (int k = 0; k < N; k++) rho[k] = (k+1)*h;

       string filecode = "_N_" + to_string(z) + "_rho_"+ to_string(y);
       mtrx-> Make_Identity(N);

//    mtrx->Tridiag(h,N,lambda_analytical);
      mtrx->Tridiag_QD_1e(h, N, rho);
//    mtrx->Tridiag_QD_2e(h, N, rho);


//         jacobi_method->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi, mtrx->A, mtrx->I);
       jacobi_method->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi_2E, mtrx->A_q, mtrx->I);
//       jacobi_method->Jacobi(N, Jacobi_t, arma_t, number_of_tests, num_transform, lambda_jacobi_E, mtrx->A_q_2e, mtrx->I);

     //  external_solvers->eigen_solvers_arma(lambda_arma, N, mtrx->A_copy);







       cout << filecode << endl;

       pf -> Prepare_results_2D(number_of_tests, N, lambda_jacobi_2E, filecode);

      /*
       pf -> Prepare_results_2B_eigenvalues(N, lambda_jacobi, lambda_analytical);
       pf -> Prepare_results_2E(number_of_tests, N, lambda_jacobi_E);
       pf -> Prepare_results_2F_egienvectors(N, mtrx-> I, lambda_jacobi_E);


    delete[] lambda_analytical; delete[] lambda_jacobi; delete[] lambda_jacobi_2E; delete[] rho; delete[] lambda_arma;
    }}


        cout << "shady" << endl;
   // cout << "Number of tests: " << number_of_tests << endl;

//   pf -> Prepare_results_2B(number_of_tests, num_transform, Jacobi_t, arma_t);



    delete[] Jacobi_t;
    delete[] arma_t;
    return 0;
}
