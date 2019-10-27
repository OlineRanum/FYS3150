#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "ReadFiles.h"


using namespace std;
using std::fstream;


vector<int> ReadFiles::Read_L_from_file()
{
    string line;
      ifstream myfile ("L.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

            L.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open L file\n";
      return L;
}

vector<int> ReadFiles::Read_T_from_file()
{
    string line;
      ifstream myfile ("T.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

            T.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open T file\n";
      return T;
}


vector<int> ReadFiles::Read_N_from_file()
{
    string line;
      ifstream myfile ("N.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

            N.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open N file\n";
      return N;
}


