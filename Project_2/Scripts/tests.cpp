#include "tests.h"

#include <iostream>
#include <armadillo>

#include "Jacobi_Method.h"

using namespace std;
using namespace arma;

void Tests::Test_max_non_diag_value()
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

void Tests::Test_eigenvalues()
{
    int test_N = 3;
    double  * a  = new double [1];
    int     * b  = new int [1];
    double  * c  = new double [test_N];

    Jacobi_Method * jack_meth = new Jacobi_Method;
    int N = 20;
    mat I = mat(N,N,fill::eye);

    mat A = mat(test_N, test_N);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 2;
    A(1, 0) = 2;
    A(1, 1) = 2;
    A(1, 2) = -1;
    A(2, 0) = 2;
    A(2, 1) = -1;
    A(2, 2) = 2;

    vec eigenval = eig_sym(A);
    for (int i = 0; i < eigenval.n_elem; i++)
        for (int j = 0; j < eigenval.n_elem; j++)
        {
            if (abs(eigenval(i) - eigenval(j)) < pow(10, -10) and i != j)
                eigenval(j) = 0;
        }

    jack_meth->Jacobi(test_N, a, 1, b, c, A, I);
    vec testres = jack_meth->lambda_jacobi;

    int teller = 0;
    if (eigenval.n_elem == testres.n_elem)
    {
        for (int i = 0; i < eigenval.n_elem; i++)
            for (int j = 0; j < testres.n_elem; j++)
            {
                if (abs(eigenval(i) - testres(j)) < pow(10.0, -10.0))
                    teller = teller + 1;
            }
        if (teller == testres.n_elem)
            cout << "Solveren for egenverdiene er flink!" << endl;
        else
        {
            cout << "Minst en av egenverdiene produsert av solveren er ikke riktige. Den har " << teller << " riktige egenverdier" << endl;
            cout << "eigenvalues: " << endl;
            cout << eigenval << endl;
            cout << "funkresultater" << endl;
            cout << testres << endl;
        }
    }
    else
    {
        cout << "eigenvalues: " << endl;
        cout << eigenval << endl;
        cout << "funkresultater" << endl;
        cout << testres << endl;
    }
}
