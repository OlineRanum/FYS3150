#include "Metropolis.h"
#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);}

int Metropolis::Random_index(int L){
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(0,L-1);
    int index= distribution(generator);
    return index;
}

void Metropolis::Estimate_Energy(mat SpinMatrix, int L, double* ME_Values){
    double E = 0;
    double M = 0;
    double J = 1;
    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++) {
            E += -J*SpinMatrix(i,j)*(
                        SpinMatrix(periodic(i, L, 1), j) +
                        SpinMatrix(i, periodic(j, L, 1))
                        ) ;
            M += SpinMatrix(i,j);
        }}
    ME_Values[0] = E;
    ME_Values[1] = M;
}

void Metropolis::Metropolis_Method(mat SpinMatrix, int L, int T, int N_mc, double* Energy, double* Magnetization)
{
    double k_b = 1;
    double beta = 1.0/(k_b*T);

    double* ME_values = new double [2];
    Estimate_Energy(SpinMatrix, L, ME_values);
    Energy[0] = ME_values[0];
    Magnetization[0] = ME_values[1];
    delete[] ME_values;

    for (int i = 1; i < N_mc; i++) {

        double* ME_values = new double [2];
        mat Fs_SpinMatrix = SpinMatrix;

        int i_s= Random_index(L); int j_s= Random_index(L);
        SpinMatrix(i_s, j_s) = -SpinMatrix(i_s, j_s);
        Estimate_Energy(SpinMatrix, L, ME_values);

        Energy[i] = ME_values[0];
        Magnetization[i] = ME_values[1];

        double dE = Energy[i]-Energy[i-1];

        if (dE > 0) {
            // If The energy is bigger than the previous, initiate probability

            random_device device;
            mt19937_64 gen(device());
            uniform_real_distribution<double> distribution(0.0,1.0);

            double r = distribution(gen);
            double P = exp(-beta*dE);

            if (r > P) {
                SpinMatrix = Fs_SpinMatrix;
                Energy[i] = Energy[i-1];
                Magnetization[i] = Magnetization[i-1];
            }}

//        cout << SpinMatrix << endl;

        delete[] ME_values;

} }
