#include "beam.h"
#include "edge.h"
#include "flatness.h"
#include "prism.h"
#include "camera.h"

#include <cmath>
#include <QDebug>


Beam::Beam(const Point& p1, const Point& p2): p1(p1), p2(p2) {}


double Beam::length() const {
	return fabs(p1.distance(p2));
}


Point Beam::vector() const {
	return p2 - p1;
}


bool Beam::orb_visible(const Point& center, const double radius) const {
	double dx = p1.get_dx(p2);
	double dy = p1.get_dy(p2);
	double dz = p1.get_dz(p2);

	double dxc = p1.get_dx(center);
	double dyc = p1.get_dy(center);
	double dzc = p1.get_dz(center);

	double t_min = (dx * dxc + dy * dyc + dz * dzc) / \
			(dx * dx + dy * dy + dz * dz);

	double min_distance = pow(dx * t_min - dxc, 2) + pow(dy * t_min - dyc, 2) + pow(dz * t_min - dzc, 2);

	return min_distance <= radius * radius;
}


bool Beam::cross_edge(const Edge& edge, Point& cross_point, double& t, const double acc) const {

	try {
		Flatness flatness = edge.egde_flatness();

		double dx = p1.get_dx(p2);
		double dy = p1.get_dy(p2);
		double dz = p1.get_dz(p2);

		double t_bottom = flatness.a * dx + flatness.b * dy + flatness.c * dz;
		double t_top = - (flatness.a * p1.get_x() + flatness.b * p1.get_y() + \
				flatness.c * p1.get_z() + flatness.d);

		if (t_bottom == 0.0) {
			t = 0.0;
			if (t_top != 0.0) {
				return false;
			}
			return edge.in_edge(p1, acc);
		}

		t = t_top / t_bottom;
		cross_point.set_x(p1.get_x() + dx * t);
		cross_point.set_y(p1.get_y() + dy * t);
		cross_point.set_z(p1.get_z() + dz * t);

		return edge.in_edge(cross_point, acc);

	} catch(std::logic_error& e) {
		return false;
	}
}


double Beam::get_angle(const Flatness& flatness) const {
	return flatness.normal().angle(-vector());
}


Beam Beam::reflected(const Flatness& flatness) const {

	double angle = get_angle(flatness);

	Point normal_vector_end(flatness.normal());
	normal_vector_end *= (length() * cos(angle) /
						  normal_vector_end.distance_zero());

	Point shift(vector() + normal_vector_end);
	Beam result(p2, p1 + shift * 2);

	return result;
}


Beam Beam::refracted(const Flatness& flatness, const double k) const {

	double angle = get_angle(flatness);

	double this_sin = sin(angle);
	double other_sin = this_sin / k;
	if (other_sin >= 1) {
		Point zero;
		Beam result(zero, zero);
		return result;
	}

	Point normal_vector_end = flatness.normal();
	normal_vector_end *= (length() * cos(angle) /
						  normal_vector_end.distance_zero());

	Point shift(vector() + normal_vector_end);
	Point other_shift(shift * (1/k));

	Beam result(p2, p2 - normal_vector_end + other_shift);

	return result;
}


bool Beam::cross_prism(const Prism& prism, Point& cross_point, Edge& cross_edge,
					   bool& got_intersection, const double acc) const {

	bool found = false;

	if (orb_visible(prism.center, prism.radius)) {

		Point buffer_cross_point;
		double t = 0;

		for(const Edge& edge : prism.side_edges) {
			if (this->cross_edge(edge, buffer_cross_point, t, acc) && (t >= 0.0)) {
				if ((p1.distance(buffer_cross_point) < p1.distance(cross_point)) || !got_intersection) {
					cross_point = buffer_cross_point;
					cross_edge = edge;
					found = true;
					got_intersection = true;
				}
			}
		}

		for(const Edge& edge : prism.top_edges) {
			if (this->cross_edge(edge, buffer_cross_point, t, acc) && (t >= 0.0)) {
				if ((p1.distance(buffer_cross_point) < p1.distance(cross_point)) || !got_intersection) {
					cross_point = buffer_cross_point;
					cross_edge = edge;
					found = true;
					got_intersection = true;
				}
			}
		}
	}

	return found;
}


bool Beam::cross_prism_with_check(const Prism& prism, Point& cross_point, Edge& cross_edge, bool& got_intersection, const double acc) const {

	bool found = false;

	if (orb_visible(prism.center, prism.radius)) {

		Point buffer_cross_point;
		double t = 0;

		for(const Edge& edge : prism.side_edges) {
			if (this->cross_edge(edge, buffer_cross_point, t, acc) && (t >= 0.0) && (t <= 1.001)) {
				if ((p1.distance(buffer_cross_point) < p1.distance(cross_point)) || !got_intersection) {
					cross_point = buffer_cross_point;
					cross_edge = edge;
					found = true;
					got_intersection = true;
				}
			}
		}

		for(const Edge& edge : prism.top_edges) {
			if (this->cross_edge(edge, buffer_cross_point, t, acc) && (t >= 0.0) && (t <= 1.001)) {
				if ((p1.distance(buffer_cross_point) < p1.distance(cross_point)) || !got_intersection) {
					cross_point = buffer_cross_point;
					cross_edge = edge;
					found = true;
					got_intersection = true;
				}
			}
		}
	}

	return found;
}
