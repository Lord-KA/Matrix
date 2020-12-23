#include "Matrix.hpp"
#include "Rationals.hpp"

int main()
{
    size_t r = 4, c = 4;
    //std::cin >> r >> c;
    
    Matrix<double> M_1(r, c), M_2(r, c), M_3(r, c);
    M_1.FillMatrix();
    M_2.FillMagickSE();
    M_3.FillMatrixOp();
    std::cout << 2 * M_1 * M_2 * 18 * M_3 - M_2 + 12 * M_1 << std::endl << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    
    Matrix<double> K_1(r, c);
    K_1.FillMatrixOp();
    std::cout << K_1 << std::endl;
    std::cout << K_1.CalcDeterminant() << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    Matrix<double> W_1(r, c), W_2(r, c), W_3(r, c), W_4(r, c);
    W_1.FillMatrix();
    W_2.FillMagickSE();
    W_3.FillMatrixOp();
    W_4.FillMatrix();
    W_4 = 14 * W_4;
    
    //std::cout << W_1.CalcDeterminant() << std::endl;
    //std::cout << W_2.CalcDeterminant() << std::endl;
    //std::cout << W_3.CalcDeterminant() << std::endl;
    //std::cout << W_4.CalcDeterminant() << std::endl;
    
    std::cout << ((W_1.CalcDeterminant() == W_1.MinorsMethod())) << std::endl;
    std::cout << ((W_2.CalcDeterminant() == W_2.MinorsMethod())) << std::endl;
    std::cout << ((W_3.CalcDeterminant() == W_3.MinorsMethod())) << std::endl;
    std::cout << ((W_4.CalcDeterminant() == W_4.MinorsMethod())) << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    Matrix<Rational> P_1(r, c);
    P_1.FillMatrixRandom(*Rationals::Random);
    std::cout << P_1 << std::endl;

    std::cout << P_1.CalcDeterminant() << std::endl;
    return 0;
}
