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
    arma::vec  Read_N_from_file();
    arma::vec Read_rho_from_file();

private:
    vector<int> v;

};



#endif // READ_N_FROM_FILE_H
