#include "flatness.h"
#include "point.h"
#include <cmath>

Flatness::Flatness(double A, double B, double C, double D): a(A), b(B), c(C), d(D) {}

bool Flatness::in_flatness(const Point& check, double acc) const {
	return (fabs(check.get_x() * a + check.get_y() * b + check.get_z() * c + d) < acc);
}

Point Flatness::normal() const {
	Point result(a, b, c);
	return result;
}
