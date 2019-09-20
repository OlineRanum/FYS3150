#include "tests.h"

#include <iostream>
#include <armadillo>

#include <Jacobi_Method.h>

using namespace std;
using namespace arma;

double Tests::test_funk(mat matrise)
{
    /* Just a testfunction for testing the tests underneath */
    vec c(matrise.n_cols); c.fill(matrise(1, 2) - 1);

    matrise.diag() = c;

    return matrise.max();
}

void Tests::Test_max_non_diag_value(void)
{
    /* Test of the function Jacobi_Method::find_max_index() */
    mat A = randu<mat> (5, 5);

    Jacobi_Method * jack_meth = new Jacobi_Method;
    jack_meth->N = 5 - 1;
    jack_meth->find_max_index(A);
    double value = jack_meth->max_element;

    int test_value = 0;
    double max_value = A.max();

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            if (value <= A(i, j) and i != j)
           {
               test_value++;
               max_value = A(i, j);
           }
        }
    if (test_value == 1)
    {
        cout << "Test successfull! Function to find max nondiagonal value worked." << endl;
    }
    else
    {
        cout << "Test unsuccessfull =(! Function to find max nondiagonal value did not work." << endl;
        cout << "Found value: " << jack_meth->max_element << endl;
        cout << "Expected value: " << max_value << endl;
    }
}

void Tests::Test_eigenvalues(void)
{
    double * a = new double [2];
    int * b = new int [2];

    Jacobi_Method * jack_meth = new Jacobi_Method;

    mat A = randu<mat> (5, 5);

    vec eigenval = eig_sym(A);
    jack_meth->Jacobi(5 - 1, a, a, 2, b, a, A);
    double * testres = new double [eigenval.n_elem]
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
