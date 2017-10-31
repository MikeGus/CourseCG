#ifndef PRISM_H
#define PRISM_H

#include <vector>
#include "point.h"
#include "edge.h"
#include "sceneobject.h"


class Prism : public SceneObject
{
	public:
		Prism(Point& global_coordinates, float reflect=0.3, float refract=0.3, float diff_reflect=0.3, float height=1, float top_rad=1, float bottom_rad=1, unsigned edge_number=3);

		void move(float dx, float dy, float dz);
		void rotate(float dxy, float dyz, float dzx);
		void resize(float k);

		std::vector<Edge> side_edges;
		std::vector<Edge> top_edges;

		float reflect;
		float refract;
		float diff_reflect;

		Point center;
		float radius;

	private:
		void setup_shell();
		void calculate_radius();


};

#endif // PRISM_H
