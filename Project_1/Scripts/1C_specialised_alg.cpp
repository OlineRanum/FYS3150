#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;


void specialized_solution (double* b, double* g, double* b_tilde, double* g_tilde, double* u, double* x, int k, int N)
{
    // setting up time check for algorithm
    clock_t st, fi;
    st = clock();

    //Forward substitution
    b_tilde[1] = b[1];
    g_tilde[1] = g[1];
    for (k = 1; k <= N-1; k++) b_tilde[k] = (k+1)/(double)k;


    for (k = 2; k <= N-2; k++) {
        g_tilde[k] = g[k] + g_tilde[k-1]/b_tilde[k-1];              // Pluss due to the fact that the offdiagonal elements reads -1
    }


    //Backward substitution -> Unnesessary as it only produces an array of N-zeros
    u[N-2] = g_tilde[N-2]/b_tilde[N-2];

    for (k = N-2; k >= 1; k--){
        u[k] = (g_tilde[k]+u[k+1])/b_tilde[k];
    }

    // calculating and printing time of algorithm
    fi = clock();
    double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    cout << "Time of specific algorithm = " << tottime << endl;
}
