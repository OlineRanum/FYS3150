#ifndef EXPECTATIONVALUES_H
#define EXPECTATIONVALUES_H


class ExpectationValues
{
public:
    void Estimate_ExpectationValues(double* Energy,double* Magnetization, int N_mc, double T, double* values);
};

#endif // EXPECTATIONVALUES_H
