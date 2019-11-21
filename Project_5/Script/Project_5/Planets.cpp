#include "Planets.h"
#include <iostream>
#include <string>
#include <cmath>

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
    x[0]  = x0;
    y[0]  = y0;
    z[0]  = z0;
    vx[0]  = vx0;
    vy[0]  = vy0;
    vz[0]  = vz0;
    r0 = sqrt(x0*x0 + y0*y0 + z0*z0);

};


