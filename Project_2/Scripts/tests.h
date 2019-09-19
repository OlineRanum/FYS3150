#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class Tests
{
public:
    double test_funk(mat matrise);
    void Test_max_non_diag_value(double funk(mat));
    void Test_eigenvalues(vec funk(mat));
};

#endif // TESTS_H
