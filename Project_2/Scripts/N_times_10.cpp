#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string.h>

using namespace std;
using std::fstream;




#include "N_times_10.h"

N_times_10::N_times_10()
{
    string line;
    vector<int> v;

      ifstream myfile ("N.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile, line) )
        {

            v.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open file" << endl;


    // Writing values to text file with latex friendly format
    fstream minfile;

    minfile.open ("N.txt", fstream::out);


    for (int i = 0; i < v.size(); i++)
    {
        for(int k = 0; k < 10; k++)
        {
            minfile  << v[i] <<  endl ;
        }
    }
    myfile.close();
}
