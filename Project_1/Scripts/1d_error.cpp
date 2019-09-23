#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
using std::fstream;


void error (double * u, double * v)
{
  for (k = 0; k <= N-1; k++) g[k] = 100 * exp( -10 * x[k] ) * pow( h2, 2 );
  for (k = 0; k <= N - 1; k++) er[k] = double log10( abs( ( v[k] - u[k] ) / u[k] ) )
}
