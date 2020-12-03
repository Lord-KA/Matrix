#include "Matrix.h"

int main()
{
    size_t r, c;
    std::cin >> r >> c;
    Matrix M(r, c);
    Matrix Zero(r, c);
    Matrix M_2(r, c);
    M_2.FillMatrickSE();
    M.FillMatrickSE();
    std::cout << M;
    std::cout << M + Zero;
    M.AddMatrix(Zero).WriteMatrix();
    std::cout << '\n' << M;
    std::cout << M_2.AddMatrix(M);
    M.AddMatrix(M_2).WriteMatrix();
    return 0;
}
