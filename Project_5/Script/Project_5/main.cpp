#include <iostream>
#include <ODESolver.h>
#include <SolarSystem.h>
#include <WriteResults.h>
#include <list>
#include <ReadFiles.h>

using namespace std;

int main()
{
    int N = 1E7;
    double t0 = 0; double tf = 20;     // Years
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
    int N_planets = 3;



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
    WR -> WR_5A(t, x, y, z, vx, vy, vz, N, "EulerN106");
    ODES -> Verlet(x, y, z, vx , vy, vz, N, h, a, 3);

    */

    // Mulitbody System


   // To run with the sun kept fixed at the center
  //  SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h, "Fix", N_planets, t);

  // To run the center of mass estimations
      SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h, "COM", N_planets, t);


// To Run for the perihelion percession estimates of Mercury, please adjust initial conditions
//    SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h, "FIXMERC", N_planets, t);

    cout << "Done" << endl;
    delete [] x; delete [] y ; delete [] z; delete [] vx; delete [] vy; delete[] vz; delete [] a;

}
