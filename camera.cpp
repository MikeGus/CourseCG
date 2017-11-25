#include "camera.h"
#include <beam.h>

Camera::Camera(const Point& coordinates, const Point& direction): coordinates(coordinates), direction(direction) {}

QPoint Camera::to_screen(const Point& p)
{
	double k = 1;

	if (p.get_z() != coordinates.get_z()) {
		k -= p.get_z() / coordinates.get_z();
	}

	QPoint point(p.get_x() / k, p.get_y() / k);
	return point;
}

bool Camera::point_visible(const Point &p) const
{
	Point check(p - coordinates);

	return (check.get_x() * direction.get_x() + \
			check.get_y() * direction.get_y() + \
			check.get_z() * direction.get_z() > 0);
}


Beam Camera::get_initial_beam(int x, int y) {

	Point p1(coordinates);
	Point p2(coordinates);

	p2.set_z(p2.get_z() - screen_distance);
	p2.set_x(p2.get_x() + x - screen_size_x_half);
	p2.set_y(p2.get_y() + y - screen_size_y_half);

	Beam initial_beam(p1, p2);

	return initial_beam;
}

