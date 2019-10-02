#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//using std::fstream;


void analytical_solution (double* x, int k, double N, double* u_anly)
{
  for (k = 0; k <= N-1; k++) u_anly[k] = 1-(1-exp(-10))*x[k]-exp(-10*x[k]);
}
