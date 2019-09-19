#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class tester
{
public:
    double test_funk(mat matrise);
    void Test_max_non_diag_value(double funk(mat));
    void Test_eigenvalues(vec funk(mat));
private:
};

#endif // TESTER_H
