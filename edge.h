#ifndef EDGE_H
#define EDGE_H
#include <vector>

class Point;

class Flatness;

class Edge {
	public:
		std::vector<Point> points;

		Flatness egde_flatness() const;
		bool in_edge(const Point& check, double acc=1e-4) const;

		bool operator==(const Edge& other) const;
};

#endif // EDGE_H
