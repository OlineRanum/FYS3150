#include "WriteResults.h"
#include "WriteResults.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

void WriteResults::WR_5A(double* x, double* y, double* z, int N){
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Results/5A/R_5A.txt", fstream::out);
    myfile << "X" << setw(15) << "Y" << setw(15) << "Z" << endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N; k++){
        if (k % (100) == 0) {
            myfile  << x[k] << setw(15) << y[k] << setw(15)<< z[k] << endl; }
    }
    myfile.close();
}
