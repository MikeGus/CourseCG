#ifndef PRISM_H
#define PRISM_H

#include <vector>
#include "point.h"
#include "edge.h"
#include "sceneobject.h"


class Prism : public SceneObject
{
	public:
		Prism() = default;
		Prism(Point& global_coordinates, double reflect=0.3, double refract=0.3, double diff_reflect=0.3, double height=1, double top_rad=1, double bottom_rad=1, unsigned edge_number=3);

		void move(double dx, double dy, double dz);

		void rotate(double dxy, double dyz, double dzx);
		void resize(double k);

		void rotate(double dxy, double dyz, double dzx, const Point& center);
		void resize(double k, const Point& center);

		void calculate_radius();


		std::vector<Edge> side_edges;
		std::vector<Edge> top_edges;

		double reflect;
		double refract;
		double diff_reflect;

		Point center;
		double radius;

};

#endif // PRISM_H
