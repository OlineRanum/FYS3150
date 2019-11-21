#ifndef PLANETS_H
#define PLANETS_H

#include <iostream>
#include <vector>

using namespace std;


class Planets
{
public:
    Planets(string name, double mass, vector<double> initialConditions);
    string m_name;
    double m_mass;
    double x0, y0, z0, vx0, vy0, vz0;

private:
};

#endif // PLANETS_H
