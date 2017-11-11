#ifndef EDGE_H
#define EDGE_H
#include <vector>
#include "flatness.h"

class Point;

class Flatness;

class Edge {
	public:
		std::vector<Point> points;
		Flatness flatness;

		bool in_edge(const Point& check, double acc=1e-4) const;

		bool operator==(const Edge& other) const;

		void setup_flatness();

};

#endif // EDGE_H
