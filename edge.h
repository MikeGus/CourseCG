#ifndef EDGE_H
#define EDGE_H
#include <vector>

class Point;

class Flatness;

class Edge {
	public:
		std::vector<Point> points;

		Flatness egde_flatness();
		bool in_edge(Point& check, float acc=1e-4);
};

#endif // EDGE_H
