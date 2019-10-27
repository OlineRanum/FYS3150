#ifndef READ_N_FROM_FILE_H
#define READ_N_FROM_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <armadillo>

using namespace std;

class ReadFiles {
public:
    vector<int>  Read_L_from_file();
    vector<int>  Read_T_from_file();
    vector<int>  Read_N_from_file();

    vector<int> L;
    vector<int> T;
    vector<int> N;

};



#endif // READ_N_FROM_FILE_H
