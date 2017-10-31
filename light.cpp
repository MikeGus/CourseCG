#include "light.h"
#include "point.h"

Light::Light(Point &coordinates, QColor intensity): coordinates(coordinates), intensity(intensity) {}

void Light::move(float dx, float dy, float dz)
{
	Point change(dx, dy, dz);
	coordinates += change;
}

void Light::rotate(float dxy, float dyz, float dzx)
{
	return;
}

void Light::resize(float k)
{
	return;
}
