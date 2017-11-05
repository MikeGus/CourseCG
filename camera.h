#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include <QPoint>
#include <QColor>

const double screen_distance = 300;
const int screen_size_x = 600;
const int screen_size_y = 480;
const int screen_size_x_half = screen_size_x / 2;
const int screen_size_y_half = screen_size_y / 2;

class Beam;

class Camera
{
	public:

		Camera(const Point& coordinates, const Point& direction);
		QPoint to_screen(const Point& p);
		bool point_visible(const Point& p) const;

		Beam get_initial_beam(int x, int y);

		Point coordinates;
		Point direction;
};

#endif // CAMERA_H
