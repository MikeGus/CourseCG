#include "light.h"
#include "point.h"

Light::Light(Point &coordinates, QColor intensity): coordinates(coordinates), intensity(intensity) {}

void Light::move(double dx, double dy, double dz)
{
	Point change(dx, dy, dz);
	coordinates += change;
}

void Light::rotate(double dxy, double dyz, double dzx)
{
	return;
}

void Light::resize(double k)
{
	return;
}
