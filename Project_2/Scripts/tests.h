#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class Tests
{
public:
    void Test_max_non_diag_value();
    void Test_eigenvalues();
};

#endif // TESTS_H
