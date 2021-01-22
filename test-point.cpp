#include "Point.h"

int main()
{
    Point p1(1.);
    Point p2(1, 2);
    Point p3(3., 4.);
    std::cout << p1 << p2 << p3 << std::endl;
}
