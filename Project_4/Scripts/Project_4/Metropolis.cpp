#include "Metropolis.h"
#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

inline int periodic(int i, int limit) {
    return (i+limit) % (limit);}


void Metropolis::Estimate_Energy(mat SpinMatrix, int L, double* ME_Values){
    double E = 0;
    double M = 0;
    double J = 1;
    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++) {
            E += -J*SpinMatrix(i,j)*(
                        SpinMatrix(periodic(i+1, L), j) +
                        SpinMatrix(i, periodic(j+1, L))
                        ) ;
            M += SpinMatrix(i,j);
        }}
    ME_Values[0] = E;
    ME_Values[1] = M;
 //   cout << "M0: " << M << " E0: " << E << endl;

}

void Metropolis::Metropolis_Method(mat SpinMatrix, int L, double T, int N_mc, double* Energy, double* Magnetization, double* AC, int rank){
    double k_b = 1;
    double beta = 1.0/(k_b*T);
    double J = 1;

    double* ME_values = new double [2];
    Estimate_Energy(SpinMatrix, L, ME_values);
    Energy[0] = ME_values[0];
    Magnetization[0] = ME_values[1];
    delete[] ME_values;
  //  cout << Magnetization[0] << endl;
  //  cout << SpinMatrix << endl;
  //  cout << "---------------" << endl;

    random_device device;
    mt19937_64 gen(device() + rank);
    uniform_real_distribution<double> distribution(0.0,1.0);

    random_device device_int;
    mt19937 generator_int(device_int() + rank);
    uniform_int_distribution<int> distribution_int(0,L-1);

    for (int i = 1; i < N_mc; i++) {

        // Time Counter
        //if (i % (N_mc/10) == 0) {cout << i/(double) N_mc*100 << "%" << endl; }

        // Select random indices
        int i_s= distribution_int(generator_int);
        int j_s= distribution_int(generator_int);


        // Estimate Implications of altering spin SpinMatrix(i_s, i_j)
        double dE = double(2*J*SpinMatrix(i_s,j_s)*(
                    SpinMatrix(periodic(i_s + 1, L), j_s) +
                    SpinMatrix(periodic(i_s - 1, L), j_s) +
                    SpinMatrix(i_s, periodic(j_s + 1, L)) +
                    SpinMatrix(i_s, periodic(j_s - 1, L))));

        double dM = -double(2*SpinMatrix(i_s, j_s));

        // If conditions are met, make transition
        if (dE <= 0 || distribution(gen) < exp(-beta*dE)) {
                SpinMatrix(i_s, j_s) *= -1;
                Energy[i] = Energy[i-1] + dE;
                AC[i] = 1;
                Magnetization[i] = Magnetization[i-1] + dM;
        }


        // If not, do not make transition
        else {  Energy[i]            = Energy[i-1];
                AC[i]                = 0;
                Magnetization[i]     = Magnetization[i-1];
            }
        /*
        cout << "E" <<i << ": " << Energy[i] << endl;
        cout << "dE" <<i << ": " << dE<< endl;
        cout << "M" <<i << ": " << Magnetization[i] << endl;
        cout << "dM" <<i << ": " << dM<< endl;
        cout << SpinMatrix << endl;
        cout << "-----------------" << endl; */

    } }
