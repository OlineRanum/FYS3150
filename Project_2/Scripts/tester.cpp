#include "tester.h"

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double tester::test_funk(mat matrise)
{
    vec c(matrise.n_cols); c.fill(matrise(1, 2) - 1);

    matrise.diag() = c;

    return matrise.max();
}

void tester::Test_max_non_diag_value(double funk(mat))
{
    mat A = randu<mat> (5, 5);
    vec a(5); a.fill(A(1, 2) - 1);
    A.diag() = a;

    double value = funk(A);
    int test_value = 0;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
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
    }
}

void tester::Test_eigenvalues(vec funk(mat))
{
    mat A = randu<mat> (5, 5);

    vec eigenval = eig_sym(A);
    vec testres = funk(A);
    int teller = 0;
    if (eigenval.n_elem == testres.n_elem)
    {
        for (int i = 0; i < eigenval.n_elem; i++)
            for (int j = 0; j < testres.n_elem; j++)
            {
                if (abs(eigenval(i) - testres(j)) < pow(10.0, -10.0))
                {
                    teller = teller + 1;
                }
            }
        if (teller == testres.n_elem)
        {
            cout << "Solveren for egenverdiene er flink!" << endl;
        }
        else
        {
            cout << "En av egenverdiene produsert av solveren er ikke riktige. Den har " << teller << " riktige egenverdier" << endl;
        }
    }
    cout << eigenval << endl;
}
