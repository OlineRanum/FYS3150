#include "gauss_legendre.h"



void Gauss_Legendre::Gauss_legendre(int n,  double a, double b, double  &integral)
{
    double * x = new double [n];
    double * w = new double [n];

    Setup *Sup = new Setup();
    Sup->gauleg(a,b,x,w,n);

    double int_gauss = 0.0;
    int i,j,k,l,f,t;

    for (int i = 0;  i < n; i++){
    for (int j = 0;  j < n; j++){
    for (int k = 0;  k < n; k++){
    for (int l = 0;  l < n; l++){
    for (int f = 0;  f < n; f++){
    for (int t = 0;  t < n; t++){
        int_gauss+=w[i]*w[j]*w[k]*w[l]*w[f]*w[t]*func_cart(x[i],x[j],x[k],x[l],x[f],x[t]);
    }}}}}}
    integral = int_gauss;
    delete [] x;
    delete [] w;
}


