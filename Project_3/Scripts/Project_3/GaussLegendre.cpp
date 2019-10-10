#include "GaussLegendre.h"
#include "WriteResults.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#define   ZERO       1.0E-8

using namespace std;

void GaussLegendre::Init_GaussLegendre(vector<int> N, double* Gauss_Legendre, int* N_values, double a, double b)
{
    // Integration as a function of N
    int iteration_counter = 0;
    for (int N_: N){
       double integral_GLeg = 0;
       int n = N_;
       N_values[iteration_counter] = N_;

        // Gauss-Legendre integration
        Calculation_GaussLegendre(n,a,b,integral_GLeg);
        printf("Gauss-Legandre:     \t%.8f\t\n", integral_GLeg);
        Gauss_Legendre[iteration_counter] = integral_GLeg;
        iteration_counter += 1;
}

}

void GaussLegendre::Calculation_GaussLegendre(int n,  double a, double b, double  &integral)
{
    double * x = new double [n];
    double * w = new double [n];

    gauleg(a,b,x,w,n);

    double int_gauss = 0.0;

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


void GaussLegendre::gauleg(double x1, double x2, double x[], double w[], int n)
{
   int         m,j,i;
   double      z1,z,xm,xl,pp,p3,p2,p1;
   double      const  pi = 3.14159265359;
   double      *x_low, *x_high, *w_low, *w_high;

   m  = (n + 1)/2;                             // roots are symmetric in the interval
   xm = 0.5 * (x2 + x1);
   xl = 0.5 * (x2 - x1);

   x_low  = x;                                       // pointer initialization
   x_high = x + n - 1;
   w_low  = w;
   w_high = w + n - 1;

   for(i = 1; i <= m; i++) {                             // loops over desired roots
      z = cos(pi * (i - 0.25)/(n + 0.5));

           /*
       ** Starting with the above approximation to the ith root
           ** we enter the mani loop of refinement bt Newtons method.
           */

      do {
         p1 =1.0;
     p2 =0.0;

       /*
       ** loop up recurrence relation to get the
           ** Legendre polynomial evaluated at x
           */

     for(j = 1; j <= n; j++) {
        p3 = p2;
        p2 = p1;
        p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3)/j;
     }

       /*
       ** p1 is now the desired Legrendre polynomial. Next compute
           ** ppp its derivative by standard relation involving also p2,
           ** polynomial of one lower order.
           */

     pp = n * (z * p1 - p2)/(z * z - 1.0);
     z1 = z;
     z  = z1 - p1/pp;                   // Newton's method
      } while(fabs(z - z1) > ZERO);

          /*
      ** Scale the root to the desired interval and put in its symmetric
          ** counterpart. Compute the weight and its symmetric counterpart
          */

      *(x_low++)  = xm - xl * z;
      *(x_high--) = xm + xl * z;
      *w_low      = 2.0 * xl/((1.0 - z * z) * pp * pp);
      *(w_high--) = *(w_low++);
   }
} // End_ function gauleg()


double GaussLegendre::func_cart(double x1, double y1, double z1, double x2, double y2, double z2){
    if  ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2) != 0)
        return exp(-4*(sqrt(x1*x1+y1*y1+z1*z1)+sqrt(x2*x2+y2*y2+z2*z2)))
                  / sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    else
        return 0;
}



