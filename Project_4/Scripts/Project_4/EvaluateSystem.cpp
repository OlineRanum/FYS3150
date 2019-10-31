#include "EvaluateSystem.h"

#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

void EvaluateSystem::Evaluate_N_4C(int n_Fractions, double* Energy, double* Abs_M, double* ME_evolution, double* MM_evolution, double* N_cycles, int N_mc, int L, double* AC, double* AC_count){
    double E = 0; double M = 0;
    double accepted_cycles = 0;
    int it_counter = 0;
    for (int i = 1; i < N_mc; i++) {
            E += Energy[i];
            M += fabs(Abs_M[i]);
            accepted_cycles += AC[i];
            if (i % 5000 == 0) {
                ME_evolution[it_counter] = (E/i)/(L*L);
                MM_evolution[it_counter] = (M/i)/(L*L);
                N_cycles[it_counter] = i;
                AC_count[it_counter] = accepted_cycles;
                it_counter += 1;
            }
    } }


