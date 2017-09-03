#include "camera.h"

Camera::Camera(const Point& coordinates, const Point& direction): coordinates(coordinates), direction(direction) {}

QPoint Camera::to_screen(const Point& p)
{
	float k = 1;
	if (p.z != coordinates.z) {
		k = 1 - p.z / coordinates.z;
	}
	QPoint point(p.x/k, p.y/k);
	return point;
}

bool Camera::point_visible(const Point &p)
{
	Point check(p.x - coordinates.x, p.y - coordinates.y, p.z - coordinates.z);
	return (check.x * direction.x + check.y * direction.y + check.z * direction.z > 0);
}
