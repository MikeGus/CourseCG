#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include <QPoint>

const float screen = 100;

class Camera
{
	public:
		Camera(const Point& coordinates, const Point& direction);

		QPoint to_screen(const Point& p);

		bool point_visible(const Point& p);

	private:
		Point coordinates;
		Point direction;
};

#endif // CAMERA_H
