#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main_3()
{
    int k;
    int N = 100;
    double h = 1/(N+1);

    double * x;
    x = new double [N];
    double * f;
    f = new double [N];

    double * a;
    a = new double [N];

    double * b;
    b = new double [N];

    double * c;
    c = new double [N];

    double * u;
    u = new double [N];

    double * l;
    l = new double [N];


    for (k = 0; k <= N; k++) x[k] = k/(double)N;
    for (k = 0; k <= N-1; k++) a[k] = -1;//*pow(h,2);
    for (k = 0; k <= N; k++) b[k] = 2;//*pow(h,2);
    for (k = 0; k <= N-1; k++) c[k] = -1;//*pow(h,2);



    u[0] = b[0];

    cout << a[1] <<'\n';
    cout << u[0] <<'\n';

    // The LU decomp
    for (k = 1; k <= N; k++) {
    l[k] = a[k]/u[k-1];
    u[k] = b[k] - l[k]*c[k-1];
    }




/*
    cout <<  "Content of vector vec:" << endl;
    for (k = 0; k <= N; k++){
    cout << f[k] << endl;
    }
*/
    fstream myfile;
    myfile.open ("matrix.txt", fstream::out);
    myfile << "X-values   f-values\n";
    for(int k = 0; k <= N-1; k++){
        myfile << l[k] << "          " <<  u[k]<< "\n" ;
    }
    myfile.close();



    delete[] x;
    delete[] f;
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
