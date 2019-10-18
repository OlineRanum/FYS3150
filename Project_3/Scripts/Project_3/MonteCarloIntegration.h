#ifndef MONTECARLOINTEGRATION_H
#define MONTECARLOINTEGRATION_H
#include <vector>
using namespace std;



class MonteCarloIntegration
{
public:
    void Init_MonteCarloIntegration(vector<int> N, double* mc, double* mc_std, int* N_values, double a, double b, int mode, int rank, double * time);
    inline double random_factor(double a, double b);
    void Estimate_MonteCarloIntegration(int n, double a, double b, double  &integral, double  &std);
    inline double random_factor_clean();
    void MonteCarlo_Importance_sampling(int n, double &integral, double &std);
    double polar_function(double r1, double t1, double p1, double r2, double t2, double p2);

    void MonteCarlo_Importance_sampling_pp(int n, double &integral, double &std, int rank);
    inline double random_factor_pp(int rank);
};

#endif // MONTECARLOINTEGRATION_H
