#include "Matrix.h"
#include <iostream>

int main()
{
    size_t r, c;
    std::cin >> r >> c;
    Matrix M(r, c);
    Matrix w;
    Matrix p(M);
    Matrix q(p), o(w);

    Matrix Zero(r, c);
    Matrix M_2(r, c);
    M_2.FillMagickSE();
    M.FillMagickSE();
    std::cout << M;
    std::cout << M + Zero*r;
    M.AddMatrix(Zero).WriteMatrix();
    std::cout << '\n' << M;
    std::cout << M_2.AddMatrix(M);
    M.AddMatrix(M_2).WriteMatrix();

    M.ReadMatrix();
    std::cout << M - M_2 * 1/3;
    return 0;
}
