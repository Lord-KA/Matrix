#include "Matrix.h"
#include "Point.h"
#include <iostream>
int main()
{
    
    size_t r = 4, c = 4;
    Matrix<Point> M(r, c), M2(r,c);
    M.FillMagickSE();
    //M2.FillMagickSE();
    //std::cout << M + M2 << std::endl;
    //std::cout << 3. * M << std::endl;
    M.WriteMatrix();
}
