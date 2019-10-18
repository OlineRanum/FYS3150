#include "WriteResults.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string.h>

using namespace arma;

using namespace std;

void WriteResults::WR_2A(double analytical, double * G_legendre, int N_test, int * N_values, double* time)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_3A.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "G-Legendre" << setw(15) << "Time" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15)<< "& "<< setw(15) << G_legendre[k] << setw(15)<< "& "<< setw(15) << time[k] << setw(15) << "\\\\" << endl;
    }
    myfile.close();

    myfile.open ("R_3A_npfriendly.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << "  ,  ";
    } myfile  << endl;

    myfile << "G_legendre: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << G_legendre[k] << "  ,  ";
    }myfile  << endl;

    myfile << "time: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << time[k] << "  ,  ";
    }
    myfile.close();
}

void WriteResults::WR_2B(double analytical, double * G_laguerre, int N_test, int * N_values, double* time)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_3B.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "G-Laguerre"  << setw(15) << "Time" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15)<< "& "<< setw(15) << G_laguerre[k] << setw(15)<< "& "<< setw(15) << time[k] << endl;
    }
    myfile.close();

    myfile.open ("R_3B_npfriendly.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << "  ,  ";
    } myfile  << endl;

    myfile << "G_laguerre: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << G_laguerre[k] << "  ,  ";
    }myfile  << endl;

    myfile << "time: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << time[k] << "  ,  ";
    }
    myfile.close();
}

void WriteResults::MC_0(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_3C.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "MC"  << setw(15) <<"MC STD" << setw(15) << "Time" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15)<< "& "<< setw(15) << mc[k] <<" & "<< setw(15) << mc_var[k] << setw(15)<< " & "<< setw(15) << time[k] << endl;
    }
    myfile.close();

    myfile.open ("R_MC_npfriendly.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << "  ,  ";
    } myfile  << endl; myfile  << endl;

    myfile << "MC: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "MC_var: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc_var[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "time: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << time[k] << "  ,  ";
    }
    myfile.close();
}


void WriteResults::MC_1(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_3D.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "MC"  << setw(15) <<"MC STD" << setw(15) << "Time" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15)<< "& "<< setw(15) << mc[k] <<" & "<< setw(15) << mc_var[k] << setw(15)<< " & "<< setw(15) << time[k] << endl;
    }
    myfile.close();

    myfile.open ("R_MC_3D_npfriendly.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << "  ,  ";
    } myfile  << endl; myfile  << endl;

    myfile << "MC: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "MC_var: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc_var[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "time: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << time[k] << "  ,  ";
    }
    myfile.close();
}

void WriteResults::MC_2(double analytical, double * mc, double * mc_var, int N_test, int * N_values, double* time)
{
    // Writing values to text file with latex friendly format
    fstream myfile;
    myfile.open ("R_3E.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N" << setw(15) << "MC"  << setw(15) <<"MC STD" << setw(15) << "Time" <<endl;
    myfile << "------------------------------------" << endl;
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << setw(15)<< "& "<< setw(15) << mc[k] <<" & "<< setw(15) << mc_var[k] << setw(15)<< " & "<< setw(15) << time[k] << endl;
    }
    myfile.close();

    myfile.open ("R_MC_3E_npfriendly.txt", fstream::out);
    //double sum_of_jac = 0;
    myfile << "Analytical Result" << setw(15) << analytical << endl;
    myfile << "------------------------------------" << endl;
    myfile << "N: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << N_values[k] << "  ,  ";
    } myfile  << endl; myfile  << endl;

    myfile << "MC: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "MC_var: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << mc_var[k] << "  ,  ";
    }myfile  << endl;myfile  << endl;

    myfile << "time: " << setw(15);
    for (int k = 0; k < N_test; k++){
        myfile  << time[k] << "  ,  ";
    }
    myfile.close();
}


