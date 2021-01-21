#include "Matrix.h"
#include <iostream>
int main()
{
    
    size_t r = 8, c = 3;
    Matrix<double> M(r, c);
    M.FillMagickSE();
    M.ReadMatrix();
    std::cout << std::endl;
    M.WriteMatrix();
}
