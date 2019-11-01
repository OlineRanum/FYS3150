#include "ExpectationValues.h"

#include <iostream>
#include <armadillo>
#include <string>



void ExpectationValues::Estimate_ExpectationValues(double* Energy, double* Magnetization, int N_mc, double T, double L, double* values){
    double k_b = 1;
    double beta = 1/(k_b*T);
    double expval_E = 0, expval_E2  = 0, expval_M = 0, expval_M2 = 0, expval_abs_M = 0;

    int BurnIn = 5000*L*L;
    std::cout << "Burn In time: " << BurnIn << std::endl;
    for (int i = BurnIn; i < N_mc; i++){
        expval_E += Energy[i];
        expval_E2 += Energy[i]*Energy[i];
        expval_M += Magnetization[i];
        expval_M2 += Magnetization[i]*Magnetization[i];
        expval_abs_M += fabs(Magnetization[i]);
       // std::cout << "M: "<< fabs(Magnetization[i]) << "  E: " << Energy[i]<< std::endl;
        if (i % 1000000 == 0) {
        }

    }

    std::cout << expval_abs_M << std::endl;
    values[0] = double(expval_E)/(N_mc-BurnIn);
    values[1] = double(expval_E2)/(N_mc-BurnIn);
    values[2] = double(expval_M)/(N_mc-BurnIn);
    values[3] = double(expval_M2)/(N_mc-BurnIn);
    values[4] = double(expval_abs_M)/(N_mc-BurnIn);

    double C_V = beta/T*(values[1] - values[0]*values[0]);
    double Chi = beta/T*(values[3] - values[2]*values[2]);
    double Chi_abs = beta/T*(values[3] - values[4]*values[4]);

    values[5] = C_V;
    values[6] = Chi;
    values[7] = Chi_abs;

    values[0] = values[0]/(L*L);
    values[1] = values[1]/(L*L);
    values[2] = values[2]/(L*L);
    values[3] = values[3]/(L*L);
    values[4] = values[4]/(L*L);
    values[5] = values[5]/(L*L);
    values[6] = values[6]/(L*L);
    values[7] = values[7]/(L*L);
}
