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
       double integral_GLegendre = 0;
       int n = N_;
       N_values[iteration_counter] = N_;

        // Gauss-Legendre integration
        Calculation_GaussLegendre(n, a, b, integral_GLegendre);
        printf("Gauss-Legendre:     \t%.8f\t\n", integral_GLegendre);

        Gauss_Legendre[iteration_counter] = integral_GLegendre;
        iteration_counter += 1;
}}

void GaussLegendre::Calculation_GaussLegendre(int n,  double a, double b, double  &integral_value)
{
    double * x = new double [n];
    double * w = new double [n];
    double integral_gauss_legandre = 0.0;

    G_Legendre_NodesWeights(a,b,x,w,n);

    for (int i = 0;  i < n; i++){
    for (int j = 0;  j < n; j++){
    for (int k = 0;  k < n; k++){
    for (int l = 0;  l < n; l++){
    for (int f = 0;  f < n; f++){
    for (int t = 0;  t < n; t++){
        integral_gauss_legandre += w[i] * w[j] * w[k] * w[l] * w[f] * w[t] *Cartesian_nodes(x[i], x[j], x[k], x[l], x[f], x[t]);
    }}}}}}

    integral_value = integral_gauss_legandre;

    delete [] x; delete [] w;
}




void GaussLegendre::G_Legendre_NodesWeights(double a, double b, double* x, double* w, int n)
{
    /* Given the integration limits a and b, the function returns arrays x and n
     * of length n. The arrays contain the abscissas and weights of the Gauss-Legendre n-point
     * quadrature formula as described by Press et al.
    */

   // Rescaling the integration limits to the interval [-1, 1]
   int mid_point  = (n + 1)/2;                                           // Due to the roots beeing symmetric in the interval, one only needs to find half of them
   double xm = 0.5 * (b + a);
   double xl = 0.5 * (b - a);

   double* x_low  = x;                                                   // pointer initialization
   double* x_high = x + n - 1;
   double* w_low  = w;
   double* w_high = w + n - 1;

   double z_guess, z_approx, poly_derivative;
   // loops over desired roots
   for(int i = 1; i <= mid_point; i++) {
      // Initial guess
      z_guess = cos(M_PI * (4*i - 1)/(4*n + 2));

      do {
         double poly_1 =1.0;
         double poly_2 =0.0;


        /* Running the recurrence relation to obtain legendre polynomial evaluated at z_guess
           Yields poly_1 which becomes the desiered Legendre polynomial
           Poly_2 is the poylnomial of one lower order from Poly_1   */

         for(int j = 1; j <= n; j++) {
            double poly_3 = poly_2;
            poly_2 = poly_1;
            poly_1 = ((2.0 * j - 1.0) * z_guess * poly_2 - (j - 1.0) * poly_3)/j;
         }


         // Computing the derivative poly_derivative of the polynomial
         poly_derivative = n * (z_guess * poly_1 - poly_2)/(z_guess * z_guess - 1.0);
         z_approx = z_guess;

         // Apply newton's method to find zeropoint
         z_guess  = z_approx - poly_1/poly_derivative ;
      } while(fabs(z_guess - z_approx) > ZERO);


      // Scaling roots and weights to interval of [-1,1], and put in symmetric counterparts
      *(x_low++)  = xm - xl * z_guess;
      *(x_high--) = xm + xl * z_guess;
      *w_low      = 2.0 * xl/((1.0 - z_guess * z_guess) * poly_derivative * poly_derivative);
      *(w_high--) = *(w_low++);
   }}


double GaussLegendre::Cartesian_nodes(double x1, double y1, double z1, double x2, double y2, double z2){
    if  ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2) != 0)
        return exp(-4*(sqrt(x1*x1+y1*y1+z1*z1)+sqrt(x2*x2+y2*y2+z2*z2)))
                  / sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
    else
        return 0;
}



