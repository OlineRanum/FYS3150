#include "WriteResults.h"
#include "WriteResults.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

void WriteResults::WR_5A(double* t, double* x, double* y, double* z, double* vx, double* vy, double* vz, int N, string filename){
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Results/5A/"+ filename + ".txt", fstream::out);
    myfile << "T" << setw(15) <<  "X" << setw(15) << "Y" << setw(15) << "Z" << setw(15)<< "VX" << setw(15) << "VY" << setw(15) << "VZ" << endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N; k++){
        if (k % (N/1000) == 0) {
            myfile  << t[k] << setw(15) << x[k] << setw(15) << y[k] << setw(15)<< z[k] << setw(15)<< vx[k] << setw(15) << vy[k] << setw(15)<< vz[k] << endl; }
    }
    myfile.close();
}


void WriteResults::WR_5D(double* t, double* x, double* y, double* z, double* vx, double* vy, double* vz, int N, string filename){
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Results/5D/"+ filename + ".txt", fstream::out);
    myfile << "T" << setw(15) <<  "X" << setw(15) << "Y" << setw(15) << "Z" << setw(15)<< "VX" << setw(15) << "VY" << setw(15) << "VZ" << endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N; k++){
        if (k % (N/1000) == 0) {
            myfile  << t[k] << setw(15) << x[k] << setw(15) << y[k] << setw(15)<< z[k] << setw(15)<< vx[k] << setw(15) << vy[k] << setw(15)<< vz[k] << endl; }
    }
    myfile.close();
}


void WriteResults::WR_5E(double* t, double* x, double* y, double* z, double* vx, double* vy, double* vz, int N, string filename){
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("../../Results/ThreeBody/"+ filename + "_COM.txt", fstream::out);
    myfile << "T" << setw(15) << "X" << setw(15) << "Y" << setw(15) << "Z" << setw(15)<< "VX" << setw(15) << "VY" << setw(15) << "VZ" << endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N; k++){
        if((k%100) == 0){
            myfile  << t[k] << setw(15) << x[k] << setw(15) << y[k] << setw(15)<< z[k] << setw(15)<< vx[k] << setw(15) << vy[k] << setw(15)<< vz[k] << endl;
        }
    }
    myfile.close();
}
