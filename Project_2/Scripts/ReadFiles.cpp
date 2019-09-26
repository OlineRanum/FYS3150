#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <armadillo>

#include "ReadFiles.h"


using namespace std;
using std::fstream;
using namespace arma;


vec ReadFiles::Read_N_from_file()
{
    string line;
    vector<int> v;

      ifstream myfile ("N.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

            v.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open file\n";
      int vSize = v.size();
      vec z = zeros<vec>(10);
      for (int k = 0; k < vSize; k++) {cout << v.at(k) <<endl; z(k) = v.at(k);}
      return z;
}

vec ReadFiles::Read_rho_from_file()
{
    string line;
    vector<int> y;

      ifstream myfile ("rho.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

            y.push_back(atoi(line.c_str()));
            cout<<"HELLOO"<<line.c_str()<<endl;
        }
        myfile.close();
      }

      else cout << "Unable to open file\n";
      cout << "AWSM";

      int ySize = y.size();
      vec w = zeros<vec>(10);
      for (int k = 0; k < ySize; k++) {cout << y.at(k) <<endl; w(k) = y.at(k);}
      return w;

}



