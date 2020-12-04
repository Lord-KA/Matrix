#include "Matrix.h"

int main()
{
    size_t r, c;
    std::cin >> r >> c;
    Matrix M(r, c);
    Matrix M_2(r, c);
    M.FillMatrix();
    M_2.FillMatrixOp();
    std::cout << M * M_2 * 2 + M << std::endl;
    Matrix M_3(r, c);
    M_3 = 2 * M * 2;
    std::cout << M_3;

    return 0;
}
