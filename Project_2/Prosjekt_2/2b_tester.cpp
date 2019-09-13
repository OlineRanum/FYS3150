#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double test_funk(mat matrise, int len_mat)
{
    double a = matrise(1, 1);
    double b;
    for (int i = 0; i <= len_mat; i++)
        for (int j = 0; j <= len_mat; j++)
        {
            b = matrise(i, j);
            if (i != j and b > a)
            {
                a = b;
            }
        }
    return a;
}

void Test_max_non_diag_value(double (*funk)(mat, int))
{
    mat A = randu<mat> (5, 5);
    vec a(5); a.fill(A(1, 2) - 1);
    A.diag() = a;

    double value = (*funk)(A, 5);
    int test_value = 0;

    for (int i = 0; i <= 5; i++)
        for (int j = 0; j <= 5; j++)
        {
            if (value <= A(i, j) and i != j)
           {
               test_value++;
           }
        }
    if (test_value == 1)
    {
        cout << "Test successfull! Function to find max nondiagonal value worked." << endl;
    }
    else
    {
        cout << "Test unsuccessfull =(! Function to find max nondiagonal value did not work." << endl;
        exit(0);
    }
}
