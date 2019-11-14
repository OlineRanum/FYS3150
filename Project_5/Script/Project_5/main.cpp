#include <iostream>
#include <ODESolver.h>
#include <WriteResults.h>

using namespace std;

int main()
{
    int N = 10000000;
    double t0 = 0; double tf = 10;
    double h = (tf-t0)/N;
    double * t = new double [N];
    for (int i=0; i <N; i ++){t[i] = t0 + i*h;}

    double * x = new double [N];
    double * y = new double [N];
    double * z = new double [N];
    double * vx = new double [N];
    double * vy = new double [N];
    double * vz = new double [N];
    double * a = new double [N];

    ODESolver *ODES        = new ODESolver();
    WriteResults *WR          = new WriteResults();

    //ODES-> ForwardEuler(x,y,z, vx,vy,vz, N,h);
    ODES-> Verlet(x, y, z, vx , vy, vz, N, h, a);

    WR -> WR_5A(x, y, z, N);
    cout << "Done" << endl;

}
