#include "ODESolver.h"
#include <iostream>
#include <cmath>
#include <Planets.h>

using namespace std;


void ODESolver::ForwardEuler(double* x, double* y, double* z, double*vx , double* vy, double* vz, int N, double h){
    double G = 4*M_PI*M_PI; double M_S = 1;
    x[0] = 1; y[0] = 0; z[0] = 0; vx[0] = 0; vy[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2); vz[0] = sqrt(G*M_S/(sqrt(x[0] + y[0] + z[0])))/sqrt(2);
  //  x[0] = 5.335858905497771E-01; y[0] =  8.370731944610594E-01; z[0] = -2.812649127895525E-05;
   // vx[0] = -1.472817722343729E-02; vy[0] =  9.288879282185889E-03; vz[0] =  -5.766212639367660E-07;
    double r0 = sqrt(x[0]*x[0] + y[0]*y[0] + z[0]*z[0]);
    double a = -G*M_S/(r0*r0*r0);

    clock_t st, fi;
    st = clock();
    for (int i = 1; i < N; i++ ){
       // if (i % (N/100) == 0) {cout << i/(double) N*100  << "%" << endl; }
        vx[i] = vx[i-1] +  h*a*x[i-1];
        vy[i] = vy[i-1] +  h*a*y[i-1];
        vz[i] = vz[i-1] +  h*a*z[i-1];
        x[i]  = x[i-1] +  h*vx[i-1];
        y[i]  = y[i-1] +  h*vy[i-1];
        z[i]  = z[i-1] +  h*vz[i-1];

        double r = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
        a = -G*M_S/(r*r*r);
    }
    fi = clock();
    double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    cout << "Euler time: " << tottime << endl;

}


void ODESolver::Verlet(double* x, double* y, double* z,  double*vx , double* vy, double* vz, int N, double h, double* a, double beta){
    double G = 4*M_PI*M_PI;double M_S = 1;

    double r0 = sqrt(x[0]*x[0] + y[0]*y[0] + z[0]*z[0]);
    a[0] = -G*M_S/(r0*pow(r0,beta));

    clock_t st, fi;
    st = clock();
    for (int i = 1; i < N; i++ ){
//        if (i % (N/100) == 0) {cout << i/(double) N*100  << "%" << endl; }

        x[i]  = x[i-1] +  h*vx[i-1] + h*h/2*a[i-1]*x[i-1];
        y[i]  = y[i-1] +  h*vy[i-1] + h*h/2*a[i-1]*y[i-1];
        z[i]  = z[i-1] +  h*vz[i-1] + h*h/2*a[i-1]*z[i-1];

        double r = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
        a[i] = -G*M_S/(r*pow(r,beta));

        vx[i] = vx[i-1]+h/2*(a[i]*x[i] + a[i-1]*x[i-1]);
        vy[i] = vy[i-1]+h/2*(a[i]*y[i] + a[i-1]*y[i-1]);
        vz[i] = vz[i-1]+h/2*(a[i]*z[i] + a[i-1]*z[i-1]);
    }
    fi = clock();
    double tottime = ( ( fi - st ) / static_cast<double> CLOCKS_PER_SEC );
    cout << "Verlet time: " << tottime << endl;


}


void ODESolver::VerletMultiBody(vector<Planets*> SolarSystem_planets, int N, double h, int N_planets, string mode){
    double G = 4*M_PI*M_PI;
    double c = 63197.8;

    int init_idx;

    if (mode == "Fix"){init_idx = 1;}
    else if (mode == "COM"){init_idx = 0;}
    else if (mode == "FIXMERC"){init_idx = 1;}

    // Setting initial acceleration
    for (int j = init_idx; j < N_planets; j++){                                                                                              // For all planets
        for (int i = 0; i < N_planets; i++){                                                                                          // For all celestial object
            if (i != j){                                                                                                              // If current planet != current relation
                double r = sqrt(abs((SolarSystem_planets[j]->x[0]-SolarSystem_planets[i]->x[0])*(SolarSystem_planets[j]->x[0]-SolarSystem_planets[i]->x[0])
                                    +(SolarSystem_planets[j]->y[0]-SolarSystem_planets[i]->y[0])*(SolarSystem_planets[j]->y[0]-SolarSystem_planets[i]->y[0])
                                    +(SolarSystem_planets[j]->z[0]-SolarSystem_planets[i]->z[0])*(SolarSystem_planets[j]->z[0]-SolarSystem_planets[i]->z[0]) ));

                 double relativistic_Factor = 1;

                 if (mode == "FIXMERC"){
                     double l = sqrt(
                                 (SolarSystem_planets[j]->y[0]*SolarSystem_planets[j]->vz[0] - SolarSystem_planets[j]->z[0]*SolarSystem_planets[j]->vy[0])*(
                                 SolarSystem_planets[j]->y[0]*SolarSystem_planets[j]->vz[0] - SolarSystem_planets[j]->z[0]*SolarSystem_planets[j]->vy[0]) +
                             (SolarSystem_planets[j]->x[0]*SolarSystem_planets[j]->vz[0] - SolarSystem_planets[j]->z[0]*SolarSystem_planets[j]->vx[0])*
                             (SolarSystem_planets[j]->x[0]*SolarSystem_planets[j]->vz[0] - SolarSystem_planets[j]->z[0]*SolarSystem_planets[j]->vx[0]) +
                                 (SolarSystem_planets[j]->x[0]*SolarSystem_planets[j]->vy[0] - SolarSystem_planets[j]->y[0]*SolarSystem_planets[j]->vx[0]) *
                                 (SolarSystem_planets[j]->x[0]*SolarSystem_planets[j]->vy[0] - SolarSystem_planets[j]->y[0]*SolarSystem_planets[j]->vx[0])
                             );
                     relativistic_Factor = 1 + 3*l*l/(r*r*c*c); }

                SolarSystem_planets[j]->ax[0] += -G*SolarSystem_planets[i]->m_mass*(SolarSystem_planets[j]->x[0] - SolarSystem_planets[i]->x[0])/(r*r*r)*relativistic_Factor;
                SolarSystem_planets[j]->ay[0] += -G*SolarSystem_planets[i]->m_mass*(SolarSystem_planets[j]->y[0] - SolarSystem_planets[i]->y[0])/(r*r*r)*relativistic_Factor;
                SolarSystem_planets[j]->az[0] += -G*SolarSystem_planets[i]->m_mass*(SolarSystem_planets[j]->z[0] - SolarSystem_planets[i]->z[0])/(r*r*r)*relativistic_Factor;
    }}}



    for (int i = 1; i < N; i++ ){                                                                                                     // For N time itterations
        if (i % (N/100) == 0) {cout << i/(double) N*100  << "%" << endl; }
        for (int j = init_idx; j < N_planets; j++){                                                                                          // For every planet
            SolarSystem_planets[j]->x[i]  = SolarSystem_planets[j]->x[i-1] +  h*SolarSystem_planets[j]->vx[i-1] + h*h/2*SolarSystem_planets[j]->ax[i-1]*SolarSystem_planets[j]->x[i-1];
            SolarSystem_planets[j]->y[i]  = SolarSystem_planets[j]->y[i-1] +  h*SolarSystem_planets[j]->vy[i-1] + h*h/2*SolarSystem_planets[j]->ay[i-1]*SolarSystem_planets[j]->y[i-1];
            SolarSystem_planets[j]->z[i]  = SolarSystem_planets[j]->z[i-1] +  h*SolarSystem_planets[j]->vz[i-1] + h*h/2*SolarSystem_planets[j]->az[i-1]*SolarSystem_planets[j]->z[i-1]; }

        for (int j = init_idx; j < N_planets; j++){
            for (int o = 0; o < N_planets; o++){
                if (o != j){
                    double r = sqrt(abs((SolarSystem_planets[j]->x[i]-SolarSystem_planets[o]->x[i])*(SolarSystem_planets[j]->x[i]-SolarSystem_planets[o]->x[i])
                                        +(SolarSystem_planets[j]->y[i]-SolarSystem_planets[o]->y[i])*(SolarSystem_planets[j]->y[i]-SolarSystem_planets[o]->y[i])
                                        +(SolarSystem_planets[j]->z[i]-SolarSystem_planets[o]->z[i])*(SolarSystem_planets[j]->z[i]-SolarSystem_planets[o]->z[i]) ));
                    //SolarSystem_planets[j]->x[i] += -G*SolarSystem_planets[o]->m_mass/(r*r*r);
                    double relativistic_Factor = 1;
                    if (mode == "FIXMERC"){
                        double l = sqrt(
                                    (SolarSystem_planets[j]->y[i-1]*SolarSystem_planets[j]->vz[i-1] - SolarSystem_planets[j]->z[i-1]*SolarSystem_planets[j]->vy[i-1])*(
                                    SolarSystem_planets[j]->y[i-1]*SolarSystem_planets[j]->vz[i-1] - SolarSystem_planets[j]->z[i-1]*SolarSystem_planets[j]->vy[i-1]) +
                                (SolarSystem_planets[j]->x[i-1]*SolarSystem_planets[j]->vz[i-1] - SolarSystem_planets[j]->z[i-1]*SolarSystem_planets[j]->vx[i-1])*
                                (SolarSystem_planets[j]->x[i-1]*SolarSystem_planets[j]->vz[i-1] - SolarSystem_planets[j]->z[i-1]*SolarSystem_planets[j]->vx[i-1]) +
                                    (SolarSystem_planets[j]->x[i-1]*SolarSystem_planets[j]->vy[i-1] - SolarSystem_planets[j]->y[i-1]*SolarSystem_planets[j]->vx[i-1]) *
                                    (SolarSystem_planets[j]->x[i-1]*SolarSystem_planets[j]->vy[i-1] - SolarSystem_planets[j]->y[i-1]*SolarSystem_planets[j]->vx[i-1]));

                        relativistic_Factor = 1+3*l*l/(r*r*c*c);}

                    SolarSystem_planets[j]->ax[i] += -G*SolarSystem_planets[o]->m_mass*(SolarSystem_planets[j]->x[i] - SolarSystem_planets[o]->x[i])/(r*r*r)*relativistic_Factor;
                    SolarSystem_planets[j]->ay[i] += -G*SolarSystem_planets[o]->m_mass*(SolarSystem_planets[j]->y[i] - SolarSystem_planets[o]->y[i])/(r*r*r)*relativistic_Factor;
                    SolarSystem_planets[j]->az[i] += -G*SolarSystem_planets[o]->m_mass*(SolarSystem_planets[j]->z[i] - SolarSystem_planets[o]->z[i])/(r*r*r)*relativistic_Factor;



                    if ((i < 200) & (j == 0)){cout << SolarSystem_planets[j]->x[i] << " " << SolarSystem_planets[o]->x[i] << endl;}
                }}

            SolarSystem_planets[j]->vx[i] = SolarSystem_planets[j]->vx[i-1] + h/2*(SolarSystem_planets[j]->ax[i] + SolarSystem_planets[j]->ax[i-1]);
            SolarSystem_planets[j]->vy[i] = SolarSystem_planets[j]->vy[i-1] + h/2*(SolarSystem_planets[j]->ay[i] + SolarSystem_planets[j]->ay[i-1]);
            SolarSystem_planets[j]->vz[i] = SolarSystem_planets[j]->vz[i-1] + h/2*(SolarSystem_planets[j]->az[i] + SolarSystem_planets[j]->az[i-1]);

        }}

}
