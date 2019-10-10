#ifndef GAUSS_LEGENDRE_H
#define GAUSS_LEGENDRE_H
#include "setup.h"

void gauleg(double x1, double x2, double x[], double w[], int n);
double func_cart(double x1, double y1, double z1, double x2, double y2, double z2);

class Gauss_Legendre
{
public:
    void Gauss_legendre(int n,  double a, double b, double  &integral);
};

#endif // GAUSS_LEGENDRE_H
