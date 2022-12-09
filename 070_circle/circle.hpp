#include <stdio.h>
#include <stdlib.h>

#include <cmath>

#include "point.hpp"
using std::abs;
using std::acos;
//using std::fmin;
using std::pow;
using std::sqrt;
#define PI acos(-1.0)

class Circle {
  Point point;
  const double radius;

 public:
  Circle(Point pt, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
