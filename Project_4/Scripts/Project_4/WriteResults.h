#ifndef WRITERESULTS_H
#define WRITERESULTS_H


class WriteResults
{
public:
    void WR_2B(int N_length, double* N, double* E, double* E2, double* M, double* M2, double* Abs_M, double* Chi, double* CV);
    void WR_2C(int Frac_length, double* E,double* Abs_M, double* N_cycles, int it_counter, double* AC);
    void WR_2D(double* E, int N_mc, int it_counter,int L);
    void WR_2E(int T_length, double* T, double* E, double* E2, double* M, double* M2, double* Abs_M, double* Chi, double* CV, int L, int it_counter);
};

#endif // WRITERESULTS_H
