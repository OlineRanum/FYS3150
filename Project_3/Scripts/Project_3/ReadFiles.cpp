#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "ReadFiles.h"


using namespace std;
using std::fstream;


vector<int> ReadFiles::Read_N_from_file()
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
      return v;
}

