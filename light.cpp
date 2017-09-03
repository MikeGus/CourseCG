#include "light.h"
#include "point.h"

Light::Light(Point &coordinates, QColor intensity): coordinates(coordinates), intensity(intensity) {}

void Light::move(float dx, float dy, float dz)
{
	coordinates.x += dx;
	coordinates.y += dy;
	coordinates.z += dz;
}

void Light::rotate(float dxy, float dyz, float dzx)
{

}

void Light::resize(float k)
{

}
