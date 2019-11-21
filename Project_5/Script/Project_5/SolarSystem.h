#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class SolarSystem
{
public:
    void CreateSolarSystem(vector<string> Names, vector<double> Mass, vector<vector<double>> initialConditions);

};

#endif // SOLARSYSTEM_H
