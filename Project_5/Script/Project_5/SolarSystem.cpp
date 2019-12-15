#include "SolarSystem.h"
#include <iostream>
#include <string>
#include <vector>
#include "Planets.h"
#include "ODESolver.h"
#include "WriteResults.h"
#include <cmath>

using namespace std;

void SolarSystem::CreateSolarSystem(vector<string> Names, vector<double> Mass, vector<vector<double>> initialConditions, int N, double h, string mode, int N_planets){

    vector<Planets*> SolarSystem_planets;
    ODESolver *ODES        = new ODESolver();
    WriteResults *WR          = new WriteResults();

    for (int i = 0; i < N_planets; i++){

        Planets* p = new Planets(Names[i], Mass[i], initialConditions[i], N);
        SolarSystem_planets.push_back(p);
        cout << p->m_name << endl;
    }

    if (mode == "Fix"){
        for (int i = 0; i < N; i++){
            SolarSystem_planets[0]->x[i]  = 0;
            SolarSystem_planets[0]->y[i]  = 0;
            SolarSystem_planets[0]->z[i]  = 0;
            SolarSystem_planets[0]->vx[i] = 0;
            SolarSystem_planets[0]->vy[i] = 0;
            SolarSystem_planets[0]->vz[i] = 0;
            SolarSystem_planets[0]->ax[i]  = 0;
            SolarSystem_planets[0]->ay[i]  = 0;
            SolarSystem_planets[0]->az[i]  = 0; }
    }
    if (mode == "COM"){

        // Setting initial velocity of sun and the center of mass system

        vector<double> R = {0, 0, 0};
        vector<double> mv = {0, 0, 0};
        double M = 0;

        for (int i = 0; i < N_planets; i++){
            mv[0]    += SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->vx[0];
            mv[1]    += SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->vy[0];
            mv[2]    += SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->vz[0];
            R[0]  +=  SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->x[0];
            R[1]  +=  SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->y[0];
            R[2]  +=  SolarSystem_planets[i]->m_mass*SolarSystem_planets[i]->z[0];
            M += SolarSystem_planets[i]->m_mass;}



        for (int i = 0; i < N_planets; i++){
            SolarSystem_planets[i]->vx[0] -= (mv[0]/M);
            SolarSystem_planets[i]->vy[0] -= (mv[1]/M);
            SolarSystem_planets[i]->vz[0] -= (mv[2]/M); }

        cout <<"HEI"<<R[0] <<endl;
        cout <<R[1] <<endl;
        cout <<R[2] <<endl;


        for (int i = 0; i < N_planets; i++){
            SolarSystem_planets[i]->x[0] -= R[0];
            SolarSystem_planets[i]->y[0] -= R[1];
            SolarSystem_planets[i]->z[0] -= R[2];
        }
    }

    ODES -> VerletMultiBody(SolarSystem_planets, N, h, N_planets, mode);

    for (int i = 0; i < N_planets; i++){
        cout << i << endl;
         WR -> WR_5E(SolarSystem_planets[i]->x, SolarSystem_planets[i]->y, SolarSystem_planets[i]->z, SolarSystem_planets[i]->vx, SolarSystem_planets[i]->vy, SolarSystem_planets[i]->vz, N, "Planet_" + SolarSystem_planets[i]->m_name);
    }

}





