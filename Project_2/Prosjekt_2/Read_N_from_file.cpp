#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>


using namespace std;
using std::fstream;


vector<int> Read_N_from_file()
{
    string line;
    vector<int> v;

      ifstream myfile ("N.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
            v.push_back(atoi(line.c_str()));
        }
        myfile.close();
      }

      else cout << "Unable to open file\n";
      for (int k: v){
         v[k];
      }
      return v;
}



