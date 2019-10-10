#ifndef GAUSSLEGENDRE_H
#define GAUSSLEGENDRE_H
#include <vector>
using namespace std;

class GaussLegendre
{
public:
    void Init_GaussLegendre(vector<int> N, double* Gauss_Legendre, int* N_values, double a, double b);
    void Calculation_GaussLegendre(int n,  double a, double b, double  &integral_value);
    void G_Legendre_NodesWeights(double a, double b, double* x, double* w, int n);
    double Cartesian_nodes(double x1, double y1, double z1, double x2, double y2, double z2);
};

#endif // GAUSSLEGENDRE_H
