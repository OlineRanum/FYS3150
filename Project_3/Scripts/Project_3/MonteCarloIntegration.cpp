#include "MonteCarloIntegration.h"
#include "GaussLegendre.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <omp.h>
#include <random>

using namespace std;
minstd_rand0 generator;


#define   ZERO       1.0E-8



void MonteCarloIntegration::Init_MonteCarloIntegration(vector<int> N, double* mc, double* mc_std, int* N_values, double a, double b, int mode, int rank)
{
    // Integration as a function of N
    int iteration_counter = 0;
    for (int N_: N){
       double integral_mc = 0;
       double std = 0;
       int n = N_;
       N_values[iteration_counter] = N_;

       if (mode == 0){
        // Monte Carlo integration
            Estimate_MonteCarloIntegration(n, a, b, integral_mc, std);
            printf("MC:     \t%.8f\t\n", integral_mc);

            mc[iteration_counter] = integral_mc;
            mc_std[iteration_counter] = std;
            iteration_counter += 1;
       }
       else if (mode == 1){
                MonteCarlo_Importance_sampling(n, integral_mc, std);
                printf("MC importance:     \t%.8f\t\n", integral_mc);

                mc[iteration_counter] = integral_mc;
                mc_std[iteration_counter] = std;
                iteration_counter += 1;
       }

       else if (mode == 2){
                MonteCarlo_Importance_sampling_pp(n, integral_mc, std, rank);
                printf("MC importance:     \t%.8f\t\n", integral_mc);

                mc[iteration_counter] = integral_mc;
                mc_std[iteration_counter] = std;
                iteration_counter += 1;
       }
}}

inline double MonteCarloIntegration::random_factor(double a, double b){
    //return ((double) generator())/2147483647;
    double intg_factor = b-a;
    random_device rd;
    mt19937_64 gen(rd());
    double r = generate_canonical < double, 128 >(gen);
    return r*intg_factor + a;
}

void MonteCarloIntegration::Estimate_MonteCarloIntegration(int n, double a, double b, double  &integral, double  &std){
    GaussLegendre *GLEG = new GaussLegendre();
    double* x = new double [n];
    double monte_carlo_integral = 0.0;
    double sigma = 0.0;

    for (int i = 0; i<n; i++){
        double x1 = random_factor(a,b);
        double y1 = random_factor(a,b);
        double z1 = random_factor(a,b);
        double x2 = random_factor(a,b);
        double y2 = random_factor(a,b);
        double z2 = random_factor(a,b);

        monte_carlo_integral += GLEG->Cartesian_nodes(x1,y1,z1,x2,y2,z2);
        x[i] = GLEG->Cartesian_nodes(x1,y1,z1,x2,y2,z2);
    }

    monte_carlo_integral = monte_carlo_integral/n;
    for (int i = 0; i < n; i++){
        double std_ = (x[i]- monte_carlo_integral);
        sigma += std_*std_;
    }
    sigma = sigma*pow(b-a,6)/n;
    std = sqrt(sigma/n);
    integral = monte_carlo_integral*pow(b-a,6);
    delete [] x;
}



inline double MonteCarloIntegration::random_factor_clean(){
    random_device rd;
    mt19937_64 gen(rd());
    return generate_canonical < double, 128 >(gen);
}



void MonteCarloIntegration::MonteCarlo_Importance_sampling(int n, double &integral, double &std){
    double* x = new double [n];
    double monte_carlo_integral = 0.0;
    double sigma = 0.0;

    for (int i = 0; i < n; i++){
        double radi_1 = -0.25*log(1-random_factor_clean());
        double radi_2 = -0.25*log(1-random_factor_clean());
        double theta_1 = M_PI*random_factor_clean();
        double theta_2 = M_PI*random_factor_clean();
        double phi_1 = 2*M_PI*random_factor_clean();
        double phi_2 = 2*M_PI*random_factor_clean();
        monte_carlo_integral += polar_function(radi_1, theta_1, phi_1, radi_2, theta_2, phi_2);;
        x[i] = polar_function(radi_1, theta_1, phi_1, radi_2, theta_2, phi_2);;
    }
    monte_carlo_integral = monte_carlo_integral/(double)n;

    for (int i = 0; i < n; i++){
        double std_ = (x[i]- monte_carlo_integral);
        sigma += std_*std_;
    }
    sigma = 0.25*sigma*pow(M_PI,4)/(n);
    std = sqrt(sigma/n);
    integral = 0.25*monte_carlo_integral*pow(M_PI,4);
    delete [] x;

}

//THE INTEGRAND FUNCTION IN POLAR COORDINATES FOR THE IMPORTANCE SAMPLING MONTE CARLO
double MonteCarloIntegration::polar_function(double r1, double t1, double p1, double r2, double t2, double p2){
    double cosb = cos(t1)*cos(t2) + sin(t1)*sin(t2)*cos(p1-p2);
    double f = r1*r1*r2*r2*sin(t1)*sin(t2)/sqrt(r1*r1+r2*r2-2*r1*r2*cosb);
    if(r1*r1+r2*r2-2*r1*r2*cosb > ZERO)
        return f;
    else
        return 0; }


inline double MonteCarloIntegration::random_factor_pp(int rank){
    //return ((double) generator())/2147483647;
    random_device rd;
    mt19937_64 gen(rd() + rank);
    return generate_canonical < double, 128 >(gen);
}



void MonteCarloIntegration::MonteCarlo_Importance_sampling_pp(int n, double &integral, double &std, int rank){
    double* x = new double [n];
    double monte_carlo_integral = 0.0;
    double sigma = 0.0;

    for (int i = 0; i < n; i++){
        double radi_1 = -0.25*log(1-random_factor_pp(rank));
        double radi_2 = -0.25*log(1-random_factor_pp(rank));
        double theta_1 = M_PI*random_factor_pp(rank);
        double theta_2 = M_PI*random_factor_pp(rank);
        double phi_1 = 2*M_PI*random_factor_pp(rank);
        double phi_2 = 2*M_PI*random_factor_pp(rank);
        monte_carlo_integral += polar_function(radi_1, theta_1, phi_1, radi_2, theta_2, phi_2);;
        x[i] = polar_function(radi_1, theta_1, phi_1, radi_2, theta_2, phi_2);;
    }
    monte_carlo_integral = monte_carlo_integral/(double)n;

    for (int i = 0; i < n; i++){
        double std_ = (x[i]- monte_carlo_integral);
        sigma += std_*std_;
    }
    sigma = 0.25*sigma*pow(M_PI,4)/(n);
    std = sqrt(sigma/n);
    integral = 0.25*monte_carlo_integral*pow(M_PI,4);
    delete [] x;

}
