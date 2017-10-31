#include "beam.h"
#include <cmath>

Beam::Beam(Point& p1, Point& p2): p1(p1), p2(p2) {}

bool Beam::orb_visible(const Point& center, const float radius) {
	float dx = p1.get_dx(p2);
	float dy = p1.get_dy(p2);
	float dz = p1.get_dz(p2);

	float dxc = p1.get_dx(center);
	float dyc = p1.get_dy(center);
	float dzc = p1.get_dz(center);

	float t_min = (dx * dxc + dy * dyc + dz * dzc) / \
			(dx * dx + dy * dy + dz * dz);

	float min_distance = pow(dx * t_min - dxc, 2) + pow(dy * t_min - dyc, 2) + pow(dz * t_min - dzc, 2);

	return min_distance <= radius * radius;
}
