#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
using std::pow;
using std::sqrt;

class Point {
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
