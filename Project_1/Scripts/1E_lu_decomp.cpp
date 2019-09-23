#include <iostream>
#include <cmath>
#include <fstream>
#include <armadillo>

using namespace std;


void LU_arma (int k, int N, double* f, double* u_LU)
{
    int n = N-2;
    arma::mat matr(n,n, arma::fill::zeros);
    //matr.diag() += 2;

    for (k = 0; k <= N-3; k++) matr(k, k) = 2;
    for (k = 0; k <= N-4; k++) matr(k, k+1) = -1;
    for (k = 1; k <= N-3; k++) matr(k, k-1) = -1;

    arma::vec b = arma::zeros(n);
    for (k = 0; k <= n-1; k++) b(k) = f[k+1];

    // setting up time check for algorithm
    clock_t st, fi;
    st = clock();
    arma::mat L, U;
    arma::lu(L,U, matr);

    arma::vec y = arma::solve(L,b);
    arma::vec x_solved = arma::solve(U,y);

    // calculating and printing time of algorithm
    fi = clock();
    double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    cout << "Time of LU algorithm = " << tottime << endl;

    u_LU[0] = 0;
    u_LU[N-1] = 0;

    for (k = 1; k <= N-2; k++) u_LU[k] = x_solved(k-1);

}
