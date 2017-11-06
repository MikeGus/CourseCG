#ifndef BEAM_H
#define BEAM_H

#include "point.h"

class Flatness;
class Edge;
class Prism;
class Camera;

class Beam {

	public:
		Point p1;
		Point p2;
		Beam() = default;
		Beam(const Point& p1, const Point& p2);

		double length() const;
		Point vector() const;

		bool orb_visible(const Point& center, const double radius) const;
		bool cross_edge(const Edge& edge, Point& cross_point,
						double& t, const double acc = 0.5) const;
		bool cross_prism(const Prism& prism, Point& cross_point, Edge& cross_edge,
						 bool& got_intersection, const double acc = 0.5) const;
		bool cross_prism_with_check(const Prism& prism, Point& cross_point, Edge& cross_edge,
									bool& got_intersection, const double acc = 0.5) const;
		Beam reflected(const Flatness& flatness) const;
		Beam refracted(const Flatness& flatness, const double k) const;

		double get_angle(const Flatness& flatness) const;
};

#endif // BEAM_H
