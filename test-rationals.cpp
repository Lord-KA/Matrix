#include "Rationals.hpp"

int main()
{
    Rational a(1, 2), b(4, 3);
    a = Rationals::rand();
    std::cout << static_cast<double>(a) << std::endl;

    return 0;
}
