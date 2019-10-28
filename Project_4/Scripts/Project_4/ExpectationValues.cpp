#include "ExpectationValues.h"

#include <iostream>
#include <armadillo>
#include <string>



void ExpectationValues::Estimate_ExpectationValues(double* Energy, double* Magnetization, int N_mc, double T, double* values){
    double k_b = 1;
    double beta = 1/(k_b*T);
    double expval_E = 0, expval_E2  = 0, expval_M = 0, expval_M2 = 0, expval_abs_M = 0;

    int BurnIn = N_mc/1000*5;
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
    values[0] = double(expval_E)/N_mc;
    values[1] = double(expval_E2)/N_mc;
    values[2] = double(expval_M)/N_mc;
    values[3] = double(expval_M2)/N_mc;
    values[4] = double(expval_abs_M)/N_mc;

    double C_V = beta/T*(values[1] - values[0]*values[0]);
    double Chi = beta/T*(values[3] - values[2]*values[2]);

    values[5] = C_V;
    values[6] = Chi;
}
