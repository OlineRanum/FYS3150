#include "SolarSystem.h"
#include <iostream>
#include <string>
#include <vector>
#include "Planets.h"

using namespace std;

void SolarSystem::CreateSolarSystem(vector<string> Names, vector<double> Mass, vector<vector<double>> initialConditions)
{
    vector<Planets*> SolarSystem_planets;

    for (int i = 0; i < 2; i++){
        Planets* p = new Planets(Names[i], Mass[i], initialConditions[i]);
        SolarSystem_planets.push_back(p);
        cout << p->m_name << endl;


}
}



