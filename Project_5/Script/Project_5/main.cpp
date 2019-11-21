#include <iostream>
#include <ODESolver.h>
#include <SolarSystem.h>
#include <WriteResults.h>
#include <list>
#include <ReadFiles.h>

using namespace std;

int main()
{
    int N = 100000000;
    double t0 = 0; double tf = 10;
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

    double * x = new double [N];
    double * y = new double [N];
    double * z = new double [N];
    double * vx = new double [N];
    double * vy = new double [N];
    double * vz = new double [N];
    double * a = new double [N];

    ODESolver *ODES        = new ODESolver();
    WriteResults *WR          = new WriteResults();
    SolarSystem *SS = new SolarSystem();
    int N_planets = 3;



    // SINGLE PLANET SYSTEM
    //ODES -> ForwardEuler(x,y,z, vx,vy,vz, N,h);
    //ODES -> Verlet(x, y, z, vx , vy, vz, N, h, a);
    //  WR -> WR_5A(x, y, z, vx, vy, vz, N);


     SS -> CreateSolarSystem(PlanetNames, PlanetMass, initialConditions, N, h);



    cout << "Done" << endl;

}
