#include "circle.hpp"

Circle::Circle(Point pt, double r) : point(pt), radius(r) {
}

void Circle::move(double dx, double dy) {
  point.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = point.distanceFrom(otherCircle.point);
  if (d >= radius + otherCircle.radius) {
    return 0.0;
  }
  else if (d <= (radius - otherCircle.radius)) {
    return PI * pow(otherCircle.radius, 2);
  }
  else if (d <= (otherCircle.radius - radius)) {
    return PI * pow(radius, 2);
  }
  else {
    double d1 = (pow(radius, 2) - pow(otherCircle.radius, 2) + pow(d, 2)) / (2 * d);
    double d2 = (pow(otherCircle.radius, 2) - pow(radius, 2) + pow(d, 2)) / (2 * d);
    double A1 =
        pow(radius, 2) * acos(d1 / radius) - d1 * sqrt(pow(radius, 2) - pow(d1, 2));
    double A2 = pow(otherCircle.radius, 2) * acos(d2 / otherCircle.radius) -
                d2 * sqrt(pow(otherCircle.radius, 2) - pow(d2, 2));
    return A1 + A2;
  }
}
