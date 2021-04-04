#include "Matrix.hpp"
#include "Rationals.hpp"

double abs(double one) {return (1?one>0:-1) * one;}

int main()
{
    size_t w = 4, q = 7;
    
    for (int r = 0; r < 10; ++r)
        for(int c = 0; c < 100; ++c){
    Matrix<double> M1(r, c), M2(r, c);
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();
    Matrix<double> M3 = M1 + M2;
    }
    std::cout << "Summing is good.\n";
    

    Matrix<double> T1(0, q), T2(q, 0);
    T1.FillMatrixRandom();
    T2.FillMatrixRandom();
    std::cout << T1 * T2 << '\n';

    return 0;
    for (int r = 0; r < 40; ++r)
        for(int c = 0; c < 40; ++c){
    Matrix<double> M1(r, c), M2(c, r);
    M1.FillMatrixRandom();
    M2.FillMatrixRandom();
    M1 * M2;
    }
    std::cout << "Multiplications is good\n";
    
}
