#include "../Matrix.hpp"
#include "Rationals.hpp"

#include <iostream>

static double abs(double one) {return (1?one>0:-1) * one;}

int main()
{
    size_t r = 4, c = 4;
    //std::cin >> r >> c;
    
    Matrix<double> M_1(r, c), M_2(r, c), M_3(r, c);

    M_1.FillMatrixRandom();
    M_2.FillMatrixRandom();
    M_3.FillMatrixRandom();
    M_1.dump(std::cout);
    std::cout << 2 * M_1 * M_2 * 18 * M_3 - M_2 + 12 * M_1 << std::endl << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    
    Matrix<double> K_1(r, c);
    K_1.FillMatrixRandom();
    std::cout << K_1 << std::endl;
    std::cout << K_1.CalcDeterminant() << std::endl;

    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    Matrix<double> W_1(r, c), W_2(r, c), W_3(r, c), W_4(r, c);
    W_1.FillMatrixRandom();
    W_2.FillMatrixRandom();
    W_3.FillMatrixRandom();
    W_4.FillMatrixRandom();
    W_4 = W_4 * 14;
    
    //std::cout << W_1.CalcDeterminant() << std::endl;
    //std::cout << W_2.CalcDeterminant() << std::endl;
    //std::cout << W_3.CalcDeterminant() << std::endl;
    //std::cout << W_4.CalcDeterminant() << std::endl;
    // return 0;       
    std::cout << ((W_1.CalcDeterminant() == W_1.MinorsMethod())) << std::endl;
    std::cout << ((W_2.CalcDeterminant() == W_2.MinorsMethod())) << std::endl;
    std::cout << ((W_3.CalcDeterminant() == W_3.MinorsMethod())) << std::endl;
    std::cout << ((W_4.CalcDeterminant() == W_4.MinorsMethod())) << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    Matrix<Rational> P_1(r, c);
    P_1.FillMatrixRandom(*Rational::Random);
    std::cout << P_1 << std::endl;

    std::cout << P_1.CalcDeterminant() << std::endl;

    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    int counter = 0;
    for (int i = 0; i < 10; ++i)
    {
        Matrix<double> Auto(r, c);
        Auto.FillMatrixRandom();
        if (abs(Auto.CalcDeterminant() - Auto.MinorsMethod()) > 1e-4){
            std::cout << "Miss" << std::endl;
            counter += 1;
        }
        else
            std::cout << "Ok" << std::endl;

    }
    std::cout << counter << " errors" << std::endl;


    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    
    return 0;
}
