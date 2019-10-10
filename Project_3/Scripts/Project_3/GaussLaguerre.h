#ifndef GAUSSLAGUERRE_H
#define GAUSSLAGUERRE_H

#include <vector>
using namespace std;


class GaussLaguerre
{
public:
    void Init_GaussLaguerre(vector<int> N, double* Gauss_Laguerre, int* N_values, double a, double b, double alpha);
    void Calculation_GaussLaguerre(int n_lag, int n_leg, double  &integral, double alpha);
    void G_Leguerre_NodesWeights(double *x, double *w, int n, double alf);
    double gammln( double xx);
    double func_polar_lag(double r1, double t1, double p1, double r2, double t2, double p2);
};

#endif // GAUSSLAGUERRE_H
