#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <armadillo>
#include <string>


class Metropolis
{
public:
    void Metropolis_Method(arma::mat SS, int L, double T, int N_mc, double* Energy, double* Magnetization,double* AC, int rank);
    void Estimate_Energy(arma::mat SpinMatrix, int L, double* ME_Values);
};

#endif // METROPOLIS_H
