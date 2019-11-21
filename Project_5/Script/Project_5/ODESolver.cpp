#include "ODESolver.h"
#include <iostream>
#include <cmath>
#include <Planets.h>

using namespace std;


void ODESolver::ForwardEuler(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h){
    double G = 1;double M_S = 1;
    x[0] = 1; y[0] = 0; z[0] = 0; vx[0] = 0; vy[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2); vz[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2);

    double r0 = sqrt(x[0]*x[0] + y[0]*y[0] + z[0]*z[0]);
    double a = -G*M_S/(r0*r0*r0);

    for (int i = 1; i < N; i++ ){
        if (i % (10000) == 0) {cout << i/(double) N  << "%" << endl; }
        vx[i] = vx[i-1] +  h*a*x[i-1];
        vy[i] = vy[i-1] +  h*a*y[i-1];
        vz[i] = vz[i-1] +  h*a*z[i-1];
        x[i]  = x[i-1] +  h*vx[i-1];
        y[i]  = y[i-1] +  h*vy[i-1];
        z[i]  = z[i-1] +  h*vz[i-1];

        double r = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
        a = -G*M_S/(r*r*r);
    }

}


void ODESolver::Verlet(double* x, double* y, double* z,  double*vx , double* vy, double* vz, int N, double h, double* a){
    double G = 1;double M_S = 1;
    x[0] = 1; y[0] = 0; z[0] = 0; vx[0] = 0; vy[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2); vz[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2);

    double r0 = sqrt(x[0]*x[0] + y[0]*y[0] + z[0]*z[0]);
    a[0] = -G*M_S/(r0*r0*r0);

    for (int i = 1; i < N; i++ ){
        if (i % (10000) == 0) {cout << i/(double) N  << "%" << endl; }

        x[i]  = x[i-1] +  h*vx[i-1] + h*h/2*a[i-1]*x[i-1];
        y[i]  = y[i-1] +  h*vy[i-1] + h*h/2*a[i-1]*y[i-1];
        z[i]  = z[i-1] +  h*vz[i-1] + h*h/2*a[i-1]*z[i-1];

        double r = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
        a[i] = -G*M_S/(r*r*r);

        vx[i] = vx[i-1]+h/2*(a[i]*x[i] + a[i-1]*x[i-1]);
        vy[i] = vy[i-1]+h/2*(a[i]*y[i] + a[i-1]*y[i-1]);
        vz[i] = vz[i-1]+h/2*(a[i]*z[i] + a[i-1]*z[i-1]);



    }

}


void ODESolver::VerletMultiBody(vector<Planets*> SolarSystem_planets, int N, double h, int N_planets){
    double G = 4*M_PI*M_PI;

    for (int j = 1; j < N_planets; j++){
        for (int i = 0; i < N_planets; i++){
            if (i != j){
                double r = sqrt(abs((SolarSystem_planets[j]->x[0]-SolarSystem_planets[i]->x[0])*(SolarSystem_planets[j]->x[0]-SolarSystem_planets[i]->x[0])
                                    +(SolarSystem_planets[j]->y[0]-SolarSystem_planets[i]->y[0])*(SolarSystem_planets[j]->y[0]-SolarSystem_planets[i]->y[0])
                                    +(SolarSystem_planets[j]->z[0]-SolarSystem_planets[i]->z[0])*(SolarSystem_planets[j]->z[0]-SolarSystem_planets[i]->z[0]) ));
                 SolarSystem_planets[j]->a[0] += -G*SolarSystem_planets[i]->m_mass/(r*r*r);
    }}}

    for (int i = 1; i < N; i++ ){
        if (i % (1000000) == 0) {cout << i/(double) N  << "%" << endl; }
        for (int j = 1; j < N_planets; j++){
            SolarSystem_planets[j]->x[i]  = SolarSystem_planets[j]->x[i-1] +  h*SolarSystem_planets[j]->vx[i-1] + h*h/2*SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->x[i-1];
            SolarSystem_planets[j]->y[i]  = SolarSystem_planets[j]->y[i-1] +  h*SolarSystem_planets[j]->vy[i-1] + h*h/2*SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->y[i-1];
            SolarSystem_planets[j]->z[i]  = SolarSystem_planets[j]->z[i-1] +  h*SolarSystem_planets[j]->vz[i-1] + h*h/2*SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->z[i-1];

            for (int o = 0; o < N_planets; o++){
                if (o != j){
                    double r = sqrt(abs((SolarSystem_planets[j]->x[i]-SolarSystem_planets[o]->x[i])*(SolarSystem_planets[j]->x[i]-SolarSystem_planets[o]->x[i])
                                        +(SolarSystem_planets[j]->y[i]-SolarSystem_planets[o]->y[i])*(SolarSystem_planets[j]->y[i]-SolarSystem_planets[o]->y[i])
                                        +(SolarSystem_planets[j]->z[i]-SolarSystem_planets[o]->z[i])*(SolarSystem_planets[j]->z[i]-SolarSystem_planets[o]->z[i]) ));
                    SolarSystem_planets[j]->a[0] += -G*SolarSystem_planets[o]->m_mass/(r*r*r);
                }}

            SolarSystem_planets[j]->vx[i] = SolarSystem_planets[j]->vx[i-1]+h/2*(SolarSystem_planets[j]->a[i]*SolarSystem_planets[j]->x[i] + SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->x[i-1]);
            SolarSystem_planets[j]->vy[i] = SolarSystem_planets[j]->vy[i-1]+h/2*(SolarSystem_planets[j]->a[i]*SolarSystem_planets[j]->y[i] + SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->y[i-1]);
            SolarSystem_planets[j]->vz[i] = SolarSystem_planets[j]->vz[i-1]+h/2*(SolarSystem_planets[j]->a[i]*SolarSystem_planets[j]->z[i] + SolarSystem_planets[j]->a[i-1]*SolarSystem_planets[j]->z[i-1]);

        }


    }}
