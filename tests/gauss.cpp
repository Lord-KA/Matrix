#include "../Matrix.hpp"
#include "Rationals.hpp"

#include <iostream>

int main()
{
    Matrix<Rational> M1(4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}), M2(4, 4), M3;
    // M1.FillMatrixRandom(*Rational::Random);
    M1.dump(std::cerr);

    // std::cout << M1.GaussianMethod();
    M2 = M1.GaussianMethod();
    M2.dump(std::cerr);

    // M3.dump(std::cerr);
}
