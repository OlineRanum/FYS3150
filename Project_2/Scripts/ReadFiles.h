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
    vector<int>  Read_N_from_file();
    vector<int> Read_rho_from_file();

private:
    vector<int> v;

};



#endif // READ_N_FROM_FILE_H
