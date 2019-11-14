#ifndef ODESOLVER_H
#define ODESOLVER_H


class ODESolver
{
public:
    void ForwardEuler(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h);
    void Verlet(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h, double* a);
};

#endif // FORWARDEULER_H
