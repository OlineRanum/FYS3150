#ifndef ODESOLVER_H
#define ODESOLVER_H
#include "Planets.h"


class ODESolver
{
public:
    void ForwardEuler(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h);
    void Verlet(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h, double* a);
    void VerletMultiBody(vector<Planets*> SolarSystem_planets, int N, double h, int N_planets);
};

#endif // FORWARDEULER_H
