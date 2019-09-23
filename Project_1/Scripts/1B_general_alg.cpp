#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include <time.h>

using namespace std;

void general_solution (double* b, double* g, double* b_tilde, double* g_tilde, double* u, double* x, int* a, int* c, int k, int N)
{
    b_tilde[1] = b[1];
    g_tilde[1] = g[1];

    // Setting up time check for algorithm
    clock_t st, fi;
    st = clock();

    //Forward substitution
    for (k = 2; k <= N-2; k++) {
        b_tilde[k] = b[k] - a[k-1]*c[k-1]/b_tilde[k-1];
        g_tilde[k] = g[k] - g_tilde[k-1]*a[k-1]/b_tilde[k-1];              // Pluss due to the fact that the offdiagonal elements reads -1
    }


    //Backward substitution -> Unnesessary as it only produces an array of N-zeros
    u[N-2] = g_tilde[N-2]/b_tilde[N-2];

    for (k = N-2; k >= 1; k--){
        u[k] = (g_tilde[k]-c[k]*u[k+1])/b_tilde[k];
    }


    // Calculating and printing time of algorithm
    fi = clock();
    double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    cout << "Time of general algorithm = " << tottime << endl;
}
