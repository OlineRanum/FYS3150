#include <iostream>
#include <ODESolver.h>
#include <SolarSystem.h>
#include <WriteResults.h>
#include <list>
#include <ReadFiles.h>

using namespace std;

int main()
{
    int N = 10E6;
    double t0 = 0; double tf = 10;     // Years
    double h = (tf-t0)/N;
    double * t = new double [N];
    for (int i=0; i <N; i ++){t[i] = t0 + i*h;}


    // Initiate Class Instances
    ReadFiles *rf             = new ReadFiles();

    // Initiate Variables
    vector<double> PlanetMass;
    vector<vector<double>> initialConditions ;
    vector<string> PlanetNames;

    // Read Variables from .txt files
    PlanetNames = rf->Read_Names_from_file();
    PlanetMass = rf->Read_Mass_from_file();

    initialConditions = rf->Read_InitialConditions_from_file();

    ODESolver *ODES        = new ODESolver();
    WriteResults *WR          = new WriteResults();
    SolarSystem *SS = new SolarSystem();
    int N_planets = 9;



    // SINGLE PLANET SYSTEM

    double * x = new double [N];
    double * y = new double [N];
    double * z = new double [N];
    double * vx = new double [N];
    double * vy = new double [N];
    double * vz = new double [N];
    double * a = new double [N];
/*
    ODES -> ForwardEuler(x,y,z, vx,vy,vz, N,h);
    WR -> WR_5A(t, x, y, z, vx, vy, vz, N, "Euler");
*/

    /*
    double * beta = new double [10];
    for (int o = 0;  o < 10; o++){
        beta[0] = 2.1 + o*1e-1;
    }

    for (int o = 0; o < 10; o++){

    for (int i = 0; i < N; i ++){
        x[i] = 0; y[i] = 0; z[i] = 0;
        vx[i] = 0; vy[i] = 0; vz[i] = 0;
    }

    double velocity_value = 8;
    x[0] = 1; y[0] = 0; z[0] = 0;
    vx[0] = 0;
    double G = 4*M_PI*M_PI;double M_S = 1;
    vy[0] = velocity_value/sqrt(2); vz[0] = velocity_value/sqrt(2);

    cout <<velocity_value << endl;


    ODES -> Verlet(x, y, z, vx , vy, vz, N, h, a, 2.9);
    WR -> WR_5D(t, x, y, z, vx, vy, vz, N, "Verlet_vel2" + to_string(o));
    }

*/

    // Mulitbody System

  //  SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h, "COM", N_planets);


     SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h, "Fix", 2);

    cout << "Done" << endl;
    delete [] x; delete [] y ; delete [] z; delete [] vx; delete [] vy; delete[] vz; delete [] a;

}
