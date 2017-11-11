#include "prism.h"
#include "edge.h"
#include "point.h"
#include <cmath>
#include <QDebug>

const unsigned MINEDGENUM = 3;

Prism::Prism(Point& global_coordinates, double reflect, double refract, double diff_reflect,
			 double height, double top_rad, double bottom_rad, unsigned edge_number): reflect(reflect),
	refract(refract), diff_reflect(diff_reflect)
{
	if (edge_number < MINEDGENUM) {
		edge_number = MINEDGENUM;
	}

	Point buffer_top(global_coordinates);
	Point buffer_bottom(buffer_top);

	buffer_top.set_y(buffer_top.get_y() - height);

	center = global_coordinates;
	center.set_y(center.get_y() - height / 2);

	double fi = 0;
	double dfi = M_PI * 2 / edge_number;

	Edge top_edge;
	Edge bottom_edge;

	for (unsigned i = 0; i < edge_number; ++i) {

		double cos_fi = cos(fi);
		double sin_fi = sin(fi);

		buffer_bottom.set_z(global_coordinates.get_z() + bottom_rad * cos_fi);
		buffer_bottom.set_x(global_coordinates.get_x() + bottom_rad * sin_fi);
		bottom_edge.points.push_back(buffer_bottom);

		buffer_top.set_z(global_coordinates.get_z() + top_rad * cos_fi);
		buffer_top.set_x(global_coordinates.get_x() + top_rad * sin_fi);
		top_edge.points.push_back(buffer_top);

		fi += dfi;
	}

	Edge buffer;
	for (unsigned i = 0; i < edge_number - 1; ++i) {

		buffer.points.push_back(top_edge.points[i]);
		if (top_rad != 0) {
			buffer.points.push_back(top_edge.points[i + 1]);
		}

		buffer.points.push_back(bottom_edge.points[i + 1]);
		if (bottom_rad != 0) {
			buffer.points.push_back(bottom_edge.points[i]);
		}

		buffer.setup_flatness();
		side_edges.push_back(buffer);
		buffer.points.clear();
	}

	buffer.points.push_back(top_edge.points[edge_number - 1]);
	if (top_rad != 0) {
		buffer.points.push_back(top_edge.points[0]);
	}
	buffer.points.push_back(bottom_edge.points[0]);
	if (bottom_rad !=0) {
		buffer.points.push_back(bottom_edge.points[edge_number - 1]);
	}

	buffer.setup_flatness();
	side_edges.push_back(buffer);

	if (top_rad != 0) {
		top_edge.setup_flatness();
		top_edges.push_back(top_edge);
	}

	if (bottom_rad != 0) {
		bottom_edge.setup_flatness();
		top_edges.push_back(bottom_edge);
	}

	calculate_radius();
}

void Prism::move(double dx, double dy, double dz)
{
	Point change(dx, dy, dz);
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point += change;
		}
		edge.setup_flatness();
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point += change;
		}
		edge.setup_flatness();
	}

	center += change;
}

void Prism::rotate(double dxy, double dyz, double dzx, const Point& center)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				point.rotate_dxy(dxy, center);
			}
			if (dyz != 0) {
				point.rotate_dyz(dyz, center);
			}
			if (dzx != 0) {
				point.rotate_dzx(dzx, center);
			}
		}
		edge.setup_flatness();
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				point.rotate_dxy(dxy, center);
			}
			if (dyz != 0) {
				point.rotate_dyz(dyz, center);
			}
			if (dzx != 0) {
				point.rotate_dzx(dzx, center);
			}
		}
		edge.setup_flatness();
	}

	if (dxy != 0) {
		this->center.rotate_dxy(dxy, center);
	}
	if (dyz != 0) {
		this->center.rotate_dyz(dyz, center);
	}
	if (dzx != 0) {
		this->center.rotate_dzx(dzx, center);
	}
}

void Prism::resize(double k, const Point& center)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
		edge.setup_flatness();
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
		edge.setup_flatness();
	}

	this->center = center + (this->center - center) * k;

	radius *= k;
}


void Prism::rotate(double dxy, double dyz, double dzx)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				point.rotate_dxy(dxy, center);
			}
			if (dyz != 0) {
				point.rotate_dyz(dyz, center);
			}
			if (dzx != 0) {
				point.rotate_dzx(dzx, center);
			}
		}
		edge.setup_flatness();
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				point.rotate_dxy(dxy, center);
			}
			if (dyz != 0) {
				point.rotate_dyz(dyz, center);
			}
			if (dzx != 0) {
				point.rotate_dzx(dzx, center);
			}
		}
		edge.setup_flatness();
	}
}

void Prism::resize(double k)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
		edge.setup_flatness();
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
		edge.setup_flatness();
	}

	radius *= k;
}

void Prism::calculate_radius()
{
	double max_distance = 0;
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			double distance = point.distance(center);
			if (distance > max_distance) {
				max_distance = distance;
			}
		}
	}
	radius = max_distance;
}
