#ifndef  Point_h
#define  Point_h

#include <ostream>

class Point;

std::ostream& operator<< (std::ostream &o, const Point &p);

class Point
{
 private:
  double x, y;
 
 public:
  Point(); //(0,0)
  Point(size_t i); //(i,i)
  Point(double d); //(d,d)
  Point(double x, double y); //(x,y)

  friend std::ostream& operator<< (std::ostream &o, const Point &p); //(0,0)
};

#endif //Point_h
