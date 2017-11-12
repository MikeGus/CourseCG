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


void Light::rotate(double dxy, double dyz, double dzx, const Point& center)
{
	if (dxy != 0) {
		coordinates.rotate_dxy(dxy, center);
	}
	if (dyz != 0) {
		coordinates.rotate_dyz(dyz, center);
	}
	if (dzx != 0) {
		coordinates.rotate_dzx(dzx, center);
	}
}

void Light::resize(double k, const Point& center)
{
	coordinates = center + (coordinates - center) * k;
	return;
}
