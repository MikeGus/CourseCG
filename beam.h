#ifndef BEAM_H
#define BEAM_H

#include "point.h"

class Beam {

	public:
		Point p1;
		Point p2;
		Beam(Point& p1, Point& p2);

		bool orb_visible(const Point& center, const float radius);

};

#endif // BEAM_H
