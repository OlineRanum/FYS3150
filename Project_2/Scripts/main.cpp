#include <iostream>
#include <fstream>
#include <vector>
#include "Read_N_from_file.h"


using namespace std;

void test (int N, double h, double* lambda_);

int main()
{
    double gamma = 3.0;
    double F = 2;
    double L = 1;
    ReadFiles *rf = new ReadFiles();
    vector<int> v;
    v = rf->Read_N_from_file();


    for (int z: v){
       int N = z;
       //cout << N <<'\n';

       double * x;
       x = new double [N];

       double * lambda_;
       lambda_ = new double [N];

       double h = 1/(double)(N);

       test(N, h, lambda_);

       for (int k = 0; k < N; k++) x[k] = k*h;
      // for (int k = 0; k < N; k++) cout << x[k]<< endl;

       cout << "Sucess\n" << endl;
    }

    return 0;
}
