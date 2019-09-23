#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
//#include <armadillo>

using namespace std;

// Must be in same folder as analytical_solution.cpp
void fh (double* vec, int k, double N, double* f);
void analytical_solution (double* x, int k, double N, double* u_anly);
void specialized_solution (double* b,double* g,double* b_tilde, double* g_tilde, double* u, double* x, int k, int N);
void general_solution (double* b, double* g, double* b_tilde, double* g_tilde, double* u, double* x, int* a, int* c, int k, int N);
void error_estimation (double* error, double* u_anly, double* u, int k, int N);
void LU_arma (int k, int N, double* g, double* u_LU);

//void error (double* u, double* v);


int main(int argc, char*argv[])
{
    // size of arrays and so on
    // TAKES N AS COMMAND LINE ARGUMENT
    int k;
    int N = atoi(argv[1])+2;

    double h = 1/(double)(N-1);

    cout << "N: " << N << endl;

    // Making pointers
    double * x;
    x = new double [N];


    double * b;
    b = new double [N];

    double * b_tilde;
    b_tilde = new double [N];


    double * u;
    u = new double [N];

    double * u_anly;
    u_anly = new double [N];

   double * g;
    g = new double [N];

    double * g_tilde;
    g_tilde = new double [N];

    int * a;
    a = new int [N];

    int * c;
    c = new int [N];

    double * u_LU;
    u_LU = new double [N];


    // Setting up x and the matrix as 1D Vectors
    for (k = 0; k < N; k++) x[k] = k*h;
    for (k = 1; k < N-1; k++) b[k] = 2;
    for (k = 1; k < N-1; k++) a[k] = -1;
    for (k = 1; k < N-1; k++) c[k] = -1;
    b[0] = 0;
    b[N-1] = 0;

    // Calculating f(x)
    fh (x, k, N, g);

    // Calculating analytical solution
    analytical_solution (x, k, N, u_anly);
    LU_arma (k, N, g, u_LU);

    // Perhaps only use either the specialized or the general at one time
    specialized_solution (b,g,b_tilde,g_tilde, u,x, k, N);
  //  general_solution (b,g,b_tilde,g_tilde, u,x, a, c, k, N);


    // Writing values to text file
    fstream myfile;
    myfile.open ("1B_N_10.txt", fstream::out);
    myfile << "b" << setw(15) <<" b_tilde"<< setw(15) <<"g" << setw(15) << "g_tilde"<< setw(15)<<"u"<< setw(15)<<"x" <<setw(15) << "LU u"<<endl;
    for(int k = 0; k <= N-1; k++){
        myfile  << b[k] <<setw(15) << b_tilde[k]<<setw(15) << g[k] <<setw(15) << g_tilde[k]<<setw(15) << u[k] <<setw(15) << x[k] << setw(15) << u_LU[k] << endl ;
    }
    myfile.close();


    // Releasing
    delete[] x;
    delete[] g;
    delete[] g_tilde;
    delete[] u;
    delete[] b;
    delete[] b_tilde;
    delete[] a;
    delete[] c;
    delete[] u_anly;
    delete[] u_LU;



    return 0;
}

