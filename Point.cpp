#include "Point.h"

Point::Point()
{
    x = 0; y = 0;
}


Point::Point(double i)
{
    x = i; y = i;
}


Point::Point(double a, double b)
{
    x = a; y = b;
}

std::ostream& operator<< (std::ostream &out, const Point &p)
{
    out << '(' << p.x << ',' << p.y << ')';
    return out;
}
