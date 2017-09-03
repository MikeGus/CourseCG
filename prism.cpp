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

	buffer_top.y -= height;
	float fi = 0;
	float dfi = M_PI * 2 / edge_number;

	Edge top_edge;
	Edge bottom_edge;

	for (unsigned i = 0; i < edge_number; ++i) {
		buffer_bottom.z = global_coordinates.z + bottom_rad * cos(fi);
		buffer_bottom.x = global_coordinates.x + bottom_rad * sin(fi);
		bottom_edge.points.push_back(buffer_bottom);

		buffer_top.z = global_coordinates.z + top_rad * cos(fi);
		buffer_top.x = global_coordinates.x + top_rad * sin(fi);
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
}

void Prism::move(float dx, float dy, float dz)
{
	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point.x += dx;
			point.y += dy;
			point.z += dz;
		}
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point.x += dx;
			point.y += dy;
			point.z += dz;
		}
	}
}

void Prism::rotate(float dxy, float dyz, float dzx)
{
	Point cent = center();

	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				float x = cent.x + (point.x - cent.x) * cos(dxy) + (point.y - cent.y) * sin(dxy);
				float y = cent.y - (point.x - cent.x) * sin(dxy) + (point.y - cent.y) * cos(dxy);
				point.x = x;
				point.y = y;
			}
			if (dyz != 0) {
				float y = cent.y + (point.y - cent.y) * cos(dyz) + (point.z - cent.z) * sin(dyz);
				float z = cent.z - (point.y - cent.y) * sin(dyz) + (point.z - cent.z) * cos(dyz);
				point.y = y;
				point.z = z;
			}
			if (dzx != 0) {
				float x = cent.x + (point.x - cent.x) * cos(dzx) + (point.z - cent.z) * sin(dzx);
				float z = cent.z - (point.x - cent.x) * sin(dzx) + (point.z - cent.z) * cos(dzx);
				point.x = x;
				point.z = z;
			}
		}
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			if (dxy != 0) {
				float x = cent.x + (point.x - cent.x) * cos(dxy) + (point.y - cent.y) * sin(dxy);
				float y = cent.y - (point.x - cent.x) * sin(dxy) + (point.y - cent.y) * cos(dxy);
				point.x = x;
				point.y = y;
			}
			if (dyz != 0) {
				float y = cent.y + (point.y - cent.y) * cos(dyz) + (point.z - cent.z) * sin(dyz);
				float z = cent.z - (point.y - cent.y) * sin(dyz) + (point.z - cent.z) * cos(dyz);
				point.y = y;
				point.z = z;
			}
			if (dzx != 0) {
				float x = cent.x + (point.x - cent.x) * cos(dzx) + (point.z - cent.z) * sin(dzx);
				float z = cent.z - (point.x - cent.x) * sin(dzx) + (point.z - cent.z) * cos(dzx);
				point.x = x;
				point.z = z;
			}
		}
	}
}

void Prism::resize(float k)
{
	Point cent = center();

	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			point.x = cent.x + k * (point.x - cent.x);
			point.y = cent.y + k * (point.y - cent.y);
			point.z = cent.z + k * (point.z - cent.z);
		}
	}

	for (Edge& edge : side_edges) {
		for (Point& point : edge.points) {
			point.x = cent.x + k * (point.x - cent.x);
			point.y = cent.y + k * (point.y - cent.y);
			point.z = cent.z + k * (point.z - cent.z);
		}
	}
}

Point Prism::center()
{
	float x = 0;
	float y = 0;
	float z = 0;

	for (Edge& edge : top_edges) {
		for (Point& point : edge.points) {
			x += point.x;
			y += point.y;
			z += point.z;
		}
	}
	unsigned top_num = 2 * side_edges.size();
	x /= top_num;
	y /= top_num;
	z /= top_num;

	Point result(x, y, z);

	return result;
}
