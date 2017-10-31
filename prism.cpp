#include "prism.h"
#include "edge.h"
#include "point.h"
#include <cmath>

const unsigned MINEDGENUM = 3;

Prism::Prism(Point& global_coordinates, float reflect, float refract, float diff_reflect,
			 float height, float top_rad, float bottom_rad, unsigned edge_number): reflect(reflect),
	refract(refract), diff_reflect(diff_reflect)
{
	if (edge_number < MINEDGENUM) {
		edge_number = MINEDGENUM;
	}

	Point buffer_top(global_coordinates);
	Point buffer_bottom(buffer_top);

	buffer_top.set_y(buffer_top.get_y() - height);

	float fi = 0;
	float dfi = M_PI * 2 / edge_number;

	Edge top_edge;
	Edge bottom_edge;

	for (unsigned i = 0; i < edge_number; ++i) {

		float cos_fi = cos(fi);
		float sin_fi = sin(fi);

		buffer_bottom.set_z(global_coordinates.get_z() + bottom_rad * cos_fi);
		buffer_bottom.set_x(global_coordinates.get_x() + bottom_rad * sin_fi);
		bottom_edge.points.push_back(buffer_bottom);

		buffer_top.set_z(global_coordinates.get_z() + top_rad * cos_fi);
		buffer_top.set_x(global_coordinates.get_x() + top_rad * sin_fi);
		top_edge.points.push_back(buffer_top);

		fi += dfi;
	}

	top_edges.push_back(top_edge);
	top_edges.push_back(bottom_edge);

	Edge buffer;
	for (unsigned i = 0; i < edge_number - 1; ++i) {
		buffer.points.push_back(top_edge.points[i]);
		buffer.points.push_back(top_edge.points[i + 1]);
		buffer.points.push_back(bottom_edge.points[i + 1]);
		buffer.points.push_back(bottom_edge.points[i]);

		side_edges.push_back(buffer);
		buffer.points.clear();
	}

	buffer.points.push_back(top_edge.points[edge_number - 1]);
	buffer.points.push_back(top_edge.points[0]);
	buffer.points.push_back(bottom_edge.points[0]);
	buffer.points.push_back(bottom_edge.points[edge_number - 1]);

	side_edges.push_back(buffer);

	setup_shell();
}

void Prism::move(float dx, float dy, float dz)
{
	Point change(dx, dy, dz);
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point += change;
		}
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point += change;
		}
	}

	center += change;
}

void Prism::rotate(float dxy, float dyz, float dzx)
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
	}
}

void Prism::resize(float k)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point = center + (point - center) * k;
		}
	}

	radius *= k;
}

void Prism::setup_shell()
{
	Point combined;

	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			combined += point;
		}
	}

	unsigned top_num = 2 * side_edges.size();

	combined *= (1 / top_num);

	center = combined;
	calculate_radius();
}

void Prism::calculate_radius()
{
	float max_distance = 0;
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			float distance = point.distance(center);
			if (distance > max_distance) {
				max_distance = distance;
			}
		}
	}
	radius = max_distance;
}
