#include "Planets.h"
#include <iostream>
#include <string>

using namespace std;

Planets::Planets(string name, double mass, vector<double> initialConditions){
    m_name = name;
    m_mass = mass;
    x0  = initialConditions[0];
    y0  = initialConditions[1];
    z0  = initialConditions[2];
    vx0 = initialConditions[3];
    vy0 = initialConditions[4];
    vz0 = initialConditions[5];
};


