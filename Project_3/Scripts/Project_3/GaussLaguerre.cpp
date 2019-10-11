#include "GaussLaguerre.h"
#include <vector>
using namespace std;
#include <string>
#include <cmath>
#include "GaussLegendre.h"
#define max_iterations 10
#define EPS 3.0e-14                                                                     // Relative precision
#include <iostream>
#define   ZERO       1.0E-8


void GaussLaguerre::Init_GaussLaguerre(vector<int> N, double* Gauss_Laguerre, int* N_values, double a, double b, double alpha)
{
    // Integration as a function of N
    int iteration_counter = 0;
    for (int N_: N){
       double integral_GLaguerre = 0;
       int n = N_;
       N_values[iteration_counter] = N_;

        // Gauss-Laguerre integration
        Calculation_GaussLaguerre(n, n, integral_GLaguerre, alpha);
        printf("Gauss-Laguerre:     \t%.8f\t\n", integral_GLaguerre);

        // Gauss-Laguerre integration
        Gauss_Laguerre[iteration_counter] = integral_GLaguerre;
        iteration_counter += 1;
}}


//Gauss-Legendre Gauss-Laguerre in polar coordinates
void GaussLaguerre::Calculation_GaussLaguerre(int n_lag, int n_leg, double  &integral, double alpha){
    GaussLegendre *GL = new GaussLegendre();
    double *xlag = new double [n_lag + 1];
    double *wlag = new double [n_lag + 1];
    double *xt = new double [n_leg];
    double *wt = new double [n_leg];
    double *xp = new double [n_leg];
    double *wp = new double [n_leg];


    G_Leguerre_NodesWeights(xlag,wlag,n_lag,alpha);
    GL->G_Legendre_NodesWeights(0,M_PI,xt,wt,n_leg);
    GL->G_Legendre_NodesWeights(0,2*M_PI,xp,wp,n_leg);

    double integral_gauss_laguerre = 0.0;

    for (int i = 1;  i <= n_lag;  i++){
    for (int j = 0;  j <  n_leg;  j++){
    for (int k = 0;  k <  n_leg;  k++){
    for (int l = 1;  l <= n_lag;  l++){
    for (int f = 0;  f <  n_leg;  f++){
    for (int t = 0;  t <  n_leg;  t++){
        integral_gauss_laguerre += wlag[i]*wlag[l]*wt[j]*wp[k]*wt[f]*wp[t]*laguerre_polar(xlag[i],xt[j],xp[k],xlag[l],xt[f],xp[t]);
    }}}}}}

    integral = integral_gauss_laguerre;

    delete [] xt;
    delete [] wt;
    delete [] xp;
    delete [] wp;
    delete [] xlag;
    delete [] wlag;
}


void GaussLaguerre::G_Leguerre_NodesWeights(double *x, double *w, int n, double alpha){
    /* Given the alf, or alpha parameter of the laguerre polynomials, this function returns x and w
     * containing the abscissas and weights of the n-point Gauss-Laguerre quadrature formula.
     * The smalles absvissa is returned in x[0], the largest in x[n-1]
     * This function is based on the work of Press et al.*/
    double z, poly_derivative, poly_2, poly_1;
    // Loop over the desiered roots
    for (int i = 1; i <= n ; i++) {
        // Intital guess for the smallest root
        if (i == 1) {z = (1.0 + alpha) * (3.0 + 0.92 * alpha) / (1.0 + 2.4 * n + 1.8 * alpha);}
        // Intital guess for the second root
        else if (i == 2) {z += (15.0 + 6.25 * alpha)/(1.0 + 0.9 * alpha + 2.5 * n);}
        // Intital guess for all other roots
        else {double a_i2 = i-2; z += ((1.0 + 2.55 * a_i2) / (1.9 * a_i2) + 1.26 * a_i2 * alpha / (1.0 + 3.5 * a_i2)) * (z - x[i-2]) / (1.0 + 0.3 * alpha);}

        for (int its = 1; its <= max_iterations; its++) {
            poly_1 = 1.0;
            poly_2 = 0.0;
            for (int j = 1; j <= n; j ++) {
                double poly_3 = poly_2;
                poly_2 = poly_1;
                poly_1 = ((2 * j - 1 + alpha - z) * poly_2 - (j - 1 + alpha)*poly_3)/j;
            }

        // The derivative of the laguerre polynomial
        poly_derivative = (n * poly_1 - (n + alpha) * poly_2)/z;
        double z1 = z;
        // Applying Newtons formula
        z = z1 - poly_1/poly_derivative;
        if (fabs(z-z1) <= EPS) break;
        }
        int its;
        if (its > max_iterations) cout << "too many iterations through Gaussian-Laguerre" << endl;
        // Storing roots and weights
        x[i] = z;
        w[i] = - exp(gammln(alpha + n)-gammln((double)n))/(poly_derivative * n * poly_2);
    }}



//FUNCTIONS FOR COMPUTING THE LAGUERRE POLYNOMIALS WEIGHTS
double GaussLaguerre::gammln( double xx){
    double x,y,tmp,ser;
    static double cof[6]={76.18009172947146,-86.50532032941677,
        24.01409824083091,-1.231739572450155,
        0.1208650973866179e-2,-0.5395239384953e-5};
    int j;

    y=x=xx;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.000000000190015;
    for (j=0;j<=5;j++) ser += cof[j]/++y;
    return -tmp+log(2.5066282746310005*ser/x);
}

//THE INTEGRAND FUNCTION IN POLAR COORDINATES REDUCED FOR GAUSSIAN LAGUERRE
double GaussLaguerre::laguerre_polar(double r1, double t1, double p1, double r2, double t2, double p2){
    double cosb = cos(t1)*cos(t2) + sin(t1)*sin(t2)*cos(p1-p2);
    double f = exp(-3*(r1+r2))*r1*r1*r2*r2*sin(t1)*sin(t2)/sqrt(r1*r1+r2*r2-2*r1*r2*cosb);
    if(r1*r1+r2*r2-2*r1*r2*cosb > ZERO)
        return f;
    else
        return 0;
}
