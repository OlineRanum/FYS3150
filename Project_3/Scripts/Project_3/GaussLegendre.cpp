#include "GaussLegendre.h"
#include "WriteResults.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#define   ZERO       1.0E-8

using namespace std;

void GaussLegendre::Init_GaussLegendre(vector<int> N, double* Gauss_Legendre, int* N_values, double a, double b, double* time)
{
    // Integration as a function of N
    int iteration_counter = 0;
    for (int N_: N){

       double integral_GLegendre = 0;
       int n = N_;
       N_values[iteration_counter] = N_;

       clock_t st, fi;
       st = clock();
        // Gauss-Legendre integration
        Calculation_GaussLegendre(n, a, b, integral_GLegendre);

        fi = clock();
        double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );

        printf("Gauss-Legendre:     \t%.8f\t\n", integral_GLegendre);

        time[iteration_counter] = tottime;
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

   double abscissas_guess, abscissas_approx, poly_derivative;
   // loops over desired roots
   for(int i = 1; i <= mid_point; i++) {
      // Initial guess
      abscissas_guess = cos(M_PI * (4*i - 1)/(4*n + 2));

      do {
         double poly_1 =1.0;
         double poly_2 =0.0;


        /* Running the recurrence relation to obtain legendre polynomial evaluated at z_guess
           Yields poly_1 which becomes the desiered Legendre polynomial
           Poly_2 is the poylnomial of one lower order from Poly_1   */

         for(int j = 1; j <= n; j++) {
            double poly_3 = poly_2;
            poly_2 = poly_1;
            poly_1 = ((2.0 * j - 1.0) * abscissas_guess * poly_2 - (j - 1.0) * poly_3)/j;
         }


         // Computing the derivative poly_derivative of the polynomial
         poly_derivative = n * (abscissas_guess * poly_1 - poly_2)/(abscissas_guess * abscissas_guess - 1.0);
         abscissas_approx = abscissas_guess;

         // Apply newton's method to find zeropoint
         abscissas_guess  = abscissas_approx - poly_1/poly_derivative ;
      } while(fabs(abscissas_guess - abscissas_approx) > ZERO);


      // Scaling roots and weights to interval of [-1,1], and put in symmetric counterparts
      *(x_low++)  = xm - xl * abscissas_guess;
      *(x_high--) = xm + xl * abscissas_guess;
      *w_low      = 2.0 * xl/((1.0 - abscissas_guess * abscissas_guess) * poly_derivative * poly_derivative);
      *(w_high--) = *(w_low++);
   }}



double GaussLegendre::Cartesian_nodes(double x_1 , double  y_1 , double  z_1 , double  x_2 , double  y_2 , double  z_2 ){
    double r = (x_1 - x_2 ) * (x_1 - x_2 ) + ( y_1 - y_2 ) * ( y_1 - y_2 ) + ( z_1 - z_2 ) * ( z_1 - z_2 );
    double r_1 = x_1 *x_1 + y_1 * y_1 + z_1 * z_1;
    double r_2 = x_2 * x_2 + y_2 * y_2 + z_2 * z_2;

    if  (r != 0)
        return exp(-4*(sqrt(r_1)+sqrt(r_2))) / sqrt(r);
    else
        return 0;
}



