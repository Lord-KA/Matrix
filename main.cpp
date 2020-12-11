#include "Matrix.h"
#include <iostream>

int main()
{
    
    size_t r, c;
    std::cin >> r >> c;
    Matrix w_1(r, c);
    w_1.ReadMatrix();
    std::cout << w_1 + 5 * w_1 << std::endl;

    Matrix w_2 = .33 * w_1;
    w_2.WriteMatrix();
    std::cout << "@@@@@@@@@@@@" << std::endl;
 
    Matrix q;
    q.ReadMatrix();
    std::cout << q;
}
