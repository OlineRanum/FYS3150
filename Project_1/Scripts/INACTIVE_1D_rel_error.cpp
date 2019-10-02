#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//using std::fstream;

// THIS FUNCTION IS NO LONGER IN USE

void error_estimation (double* error, double* u_anly, double* u, int k, int N)
{
  error[0] = 0;
  error[N-1] = 0;
  for (k = 1; k <= N-2; k++) error[k] = log10(abs((u[k]-u_anly[k])/u_anly[k]));         //LIKELY a round off error due to the subtracktion of almost similar numbers?
}
