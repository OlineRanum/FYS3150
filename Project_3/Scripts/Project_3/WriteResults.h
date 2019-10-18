#ifndef WRITERESULTS_H
#define WRITERESULTS_H


class WriteResults
{
public:
    void WR_2A(double analytical, double * G_legendre, int N_test, int * N_values, double* time);
    void WR_2B(double analytical, double * G_laguerre, int N_test, int * N_values, double * time);
    void MC_0(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time);
    void MC_1(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time);
    void MC_2(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time);
};

#endif // WRITERESULTS_H
