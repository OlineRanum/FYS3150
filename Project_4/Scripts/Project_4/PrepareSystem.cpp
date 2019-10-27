#include "PrepareSystem.h"
#include <iostream>
#include <armadillo>
#include <string>

using namespace std;
using namespace arma;

void PrepareSystem::PrepareSpinMatrix(int L) {
    SpinSystem = mat(L, L);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            random_device rd; mt19937_64 gen(rd());
            double r = generate_canonical < double, 128 >(gen);
            if (r <= 0.5) {SpinSystem(i,j) = -1;}
            else {SpinSystem(i,j) = 1;}
        }}
}
