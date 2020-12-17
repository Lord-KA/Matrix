#include "Rationals.hpp"

int main()
{
    Rational a(1, 2), b(4, 3);
    std::cout << a + b << ' ' << a/b << ' ' << a - b << ' ' << a * b << std::endl;

    std::cout << static_cast<double>(b) << std::endl;

    return 0;
}
