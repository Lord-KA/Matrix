#include "Matrix.h"

int main()
{
    size_t r, c;
    std::cin >> r >> c;
    Matrix M_1(r, c), M_2(r, c), M_3(r, c);
    M_1.FillMatrix();
    M_2.FillMagickSE();
    M_3.FillMatrixOp();
    std::cout << 2 * M_1 * M_2 * 18 * M_3 << std::endl;
    std::cout << M_1;

    return 0;
}
