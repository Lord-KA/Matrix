#include "Rationals.hpp"

int main()
{
    Rational a(1, 2), b(3, 4);
    std::cout << a + b << ' ' << a/b << ' ' << a - b << ' ' << a * b << std::endl;
    for (int i=2000; i < 2020; ++i)
        std::cout << Rational(i, 100) << std::endl;

    return 0;
}
