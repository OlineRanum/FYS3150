#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <armadillo>
#include <string>
#include <mpi.h>

#include "ReadFiles.h"
#include "PrepareSystem.h"
#include "Metropolis.h"
#include "ExpectationValues.h"
#include "WriteResults.h"
#include "EvaluateSystem.h"

using namespace std;
using namespace arma;

int main()
{
    cout << "COMPILEDONE" << endl;
    // Initiate Class Instances
    ReadFiles *rf             = new ReadFiles();
    WriteResults *wr          = new WriteResults();
    PrepareSystem *mtrx       = new PrepareSystem();
    Metropolis *met           = new Metropolis();
    ExpectationValues *expval = new ExpectationValues();
    EvaluateSystem *es        = new EvaluateSystem();
    
    // Initiate Variables
    vector<int> L, N ;
    vector<double> T;

    // Read Variables from .txt files
    L = rf->Read_L_from_file();
    T = rf->Read_T_from_file();
    N = rf->Read_N_from_file();
    
    // Find number of tests
    int N_length = 0; for (int n: N){N_length += 1;}

    // Initiate value pointers
    double* n_vals   = new double [N_length];
    double* ex_E     = new double [N_length];
    double* ex_E2    = new double [N_length];
    double* ex_M     = new double [N_length];
    double* ex_M2    = new double [N_length];
    double* ex_abs_M = new double [N_length];
    double* Chi      = new double [N_length];
    double* CV       = new double [N_length];

    int it_counter = 0;
    for (int n: N){
        //  Initiate current storage 
        double* Acp_config          = new double [n];
        double* Acp_config_count     = new double [n];
        double * Energy_values              = new double [n];
        double * Magnetization              = new double [n];
        double * Expectation_Values         = new double [8];
        double * Expectation_Values_         = new double [8];
        
//        cout << "L: " << L[0] << endl << "T: " << T[0] << endl << "N: " << n << endl;

        // Prepatre Systems

    //    mtrx-> PrepareSpinMatrix_Random(L[0]);
         mtrx-> PrepareSpinMatrix_Ordered(L[0], 1);
        
 //        met -> Metropolis_Method(mtrx->SpinSystem, L[0], T[0], n , Energy_values, Magnetization, Acp_config);


        //---- B ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
        /*
        expval -> Estimate_ExpectationValues(Energy_values, Magnetization, n, T[0],L[0],  Expectation_Values);

        cout << "<E>      = " << Expectation_Values[0] << endl;
        cout << "<E2>     = " << Expectation_Values[1] << endl;
        cout << "<M>      = " << Expectation_Values[2] << endl;
        cout << "<M2>     = " << Expectation_Values[3] << endl;
        cout << "<abs(M)> = " << Expectation_Values[4] << endl;
        cout << "C_V      = " << Expectation_Values[5] << endl;
        cout << "CHI      = " << Expectation_Values[6] << endl;

        n_vals[it_counter] = n;
        ex_E[it_counter]     = Expectation_Values[0];
        ex_E2[it_counter]    = Expectation_Values[1];
        ex_M[it_counter]     = Expectation_Values[2];
        ex_M2[it_counter]    = Expectation_Values[3];
        ex_abs_M[it_counter] = Expectation_Values[4];
        CV[it_counter]      = Expectation_Values[5];
        Chi[it_counter]      = Expectation_Values[6];
        */

        //---- C ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
        /*
        int n_Fractions = 2*n/10000-1;
        cout << "FRAC: "<< n_Fractions << endl;
        double * Mean_Energy_evolution = new double [n_Fractions];
        double * Mean_Magnetization_evolution = new double [n_Fractions];
        double * N_cycle = new double [n_Fractions];
        //es-> Evaluate_N_4C(n_Fractions, Energy_values, Magnetization, Mean_Energy_evolution, Mean_Magnetization_evolution, N_cycle, n, L[0], Acp_config, Acp_config_count);
        //wr -> WR_2C(n_Fractions, Mean_Energy_evolution, Mean_Magnetization_evolution, N_cycle, it_counter, Acp_config_count);
        delete [] Mean_Energy_evolution; delete [] Mean_Magnetization_evolution; delete[] N_cycle;
        */

        //---- D ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

     //    wr -> WR_2D(Energy_values, n, it_counter, 1);



        //---- E ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
        double dT = 0.01;
        int T_r = int(0.35/dT);
        double* T_range = new double [T_r];

        for (int i = 0; i < T_r; i ++){T_range[i] = 2.15 + i*dT;}

        double* t_vals_   = new double [T_r];
        double* ex_E_     = new double [T_r];
        double* ex_E2_    = new double [T_r];
        double* ex_M_     = new double [T_r];
        double* ex_M2_    = new double [T_r];
        double* ex_abs_M_ = new double [T_r];
        double* Chi_      = new double [T_r];
        double* CV_       = new double [T_r];


        int it_counter_ = 0;


        MPI_Init(NULL, NULL);
        int numprocs; int my_rank;

        double* local_sum = new double[8];
        double* total_sum = new double[8];

        for (int i = 0; i < T_r; i++){
           // cout << "T:" << T_range[i] << endl;

            MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
            MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
            double time_start = MPI_Wtime();

            met -> Metropolis_Method(mtrx->SpinSystem, L[0], T_range[i], n , Energy_values, Magnetization, Acp_config, my_rank);

            expval -> Estimate_ExpectationValues(Energy_values, Magnetization, n, T_range[i], L[0],  Expectation_Values);




            for (int o = 0; o < 8; o ++){local_sum[o] = 0; total_sum[o] = 0;}
            for (int o = 0; o < 8; o ++){local_sum[o] = Expectation_Values[o]; total_sum[o] = 0;}




            MPI_Reduce(local_sum, total_sum, 8, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            double time_end = MPI_Wtime();


            double total_time = time_end-time_start;

            if ( my_rank == 0) {

                   for (int j = 0; j <8; j++){
                       Expectation_Values_[j] = total_sum[j]/4;
                    //   cout << "Total sum: " << total_sum[j] << endl;
                   }
                  // cout << "Time = " <<  total_time  << " on number of processors: "  << numprocs  << endl;
                   cout << total_time << " , " << endl;
                   t_vals_[it_counter_]   = T_range[i];
                   ex_E_[it_counter_]     = Expectation_Values_[0];
                 //  cout <<"T: "<< T_range[i] << " EXP E VAL: " << Expectation_Values_[0]<< endl;
                   ex_E2_[it_counter_]    = Expectation_Values_[1];
                   ex_M_[it_counter_]     = Expectation_Values_[2];
                   ex_M2_[it_counter_]    = Expectation_Values_[3];
                   ex_abs_M_[it_counter_] = Expectation_Values_[4];
                   CV_[it_counter_]       = Expectation_Values_[5];
                   Chi_[it_counter_]      = Expectation_Values_[7];
                   it_counter_ += 1;
            //       cout << "-------------------------T INCREMENT -----------------------------------------------------------" << endl;
                 }


           //  delete[] local_sum; delete[] total_sum;
        ;}



        MPI_Finalize ();


        if(my_rank == 0){


            wr -> WR_2E(T_r, t_vals_, ex_E_, ex_E2_, ex_M_, ex_M2_, ex_abs_M_, Chi_, CV_, L[0], it_counter);
        }

        delete[] t_vals_; delete [] ex_E_; delete [] ex_E2_; delete [] ex_M_; delete [] ex_M2_; delete [] ex_abs_M_; delete [] Chi_; delete [] CV_;


        //---- F ---------------------------------------------------------------------------------------------------------------------------------------------------------------------




        //---- END -------------------------------------------------------------------------------------------------------------------------------------------------------------------



        it_counter +=1;
        delete [] Energy_values; delete []  Magnetization; delete [] Expectation_Values; delete [] Expectation_Values_;
        delete[] Acp_config_count; delete [] Acp_config;
    }


    //---- B 2 ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //   wr -> WR_2B(N_length, n_vals, ex_E, ex_E2, ex_M, ex_M2, ex_abs_M, Chi, CV);


    delete[] n_vals; delete [] ex_E; delete [] ex_E2; delete [] ex_M; delete [] ex_M2; delete [] ex_abs_M; delete [] Chi; delete [] CV;
}
