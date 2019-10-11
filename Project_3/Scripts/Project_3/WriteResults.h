#ifndef WRITERESULTS_H
#define WRITERESULTS_H


class WriteResults
{
public:
    void WR_2A(double analytical, double * G_legendre, int N_test, int * N_values);
    void WR_2B(double analytical, double * G_laguerre, int N_test, int * N_values);
};

#endif // WRITERESULTS_H
