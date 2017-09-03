#include "flatness.h"
#include "point.h"
#include <cmath>

Flatness::Flatness(float A, float B, float C, float D): a(A), b(B), c(C), d(D) {}

bool Flatness::in_flatness(Point& check, float acc)
{
	return (fabs(check.x * a + check.y * b + check.z * c + d) < acc);
}
