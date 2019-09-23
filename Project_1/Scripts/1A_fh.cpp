#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//using std::fstream;


void fh (double* x, int k, double N, double* g)
{
  // Function used for calculating the analytical solution
 // cout << "printed vector" << vec;
  double h2 = 1/(double)(N-1);
  for (k = 1; k < N-1; k++) g[k] = 100*exp(-10*x[k])*h2*h2;
}
