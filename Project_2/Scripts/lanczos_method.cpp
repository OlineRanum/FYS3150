#include "lanczos_method.h"

#include <iostream>
#include <cmath>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

void Lanczos_method::Lanczos(int N, double * Jacobi_t, double * arma_t, int number_of_tests, int * num_transform, double * lambda_jacobi, mat A, mat & I)
{
    mat Q = mat(N, N, fill::zeros); for (int i = 0; i < N; i++) Q(0, i) = 1;
    vec r_ = A * Q.col(0);
    vec b = r_.t() * Q.col(0);
    vec a(N); a(0) = b(0);
    mat r = mat(N, N, fill::zeros); r.col(0) = r_ - a(0) * Q.col(0);
    vec beta = vec(N, fill::zeros); beta(0) = 1;

    int i = 0;
    while (abs(beta(i) - 0) > 0.0001 and i < N - 1)
    {
        cout << "første linje" << endl;
        Q.col(i + 1) = r.col(i) / beta(i);
        cout << "andre linje" << endl;
        r_ = A * Q.col(i);
        cout << "tredje linje" << endl;
        b = Q.col(i + 1).t() * r_; a(i + 1) = b(0);
        cout << "fjerde linje" << endl;
        beta(i) = norm(r.col(i));
        cout << "femte linje" << endl;
        r.col(i + 1) = r_(i + 1) - a(i + 1) * Q.col(i + 1) - beta(i) * Q.col(i);
        cout << beta(i) << endl;
        i++;
    }
    cout << a << endl;
    cout << beta << endl;
    //int * r = new int; r =  q_1;
    //int q = 0;
    //int k = 0;
    /*while (beta != 0)
    {
        q_{k+1} = r_k/beta_k
        k = k+1
        alpha_k = q_k^T A q_k
        r_k = (A - alpha_k * I) * q_k - beta_{k - 1} * q_{k - 1}
        beta = || r_k ||_2
    }*/
}
