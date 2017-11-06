#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "point.h"

class SceneObject {
	public:
		virtual void move(double dx, double dy, double dz) = 0;

		virtual void rotate(double dxy, double dyz, double dzx) = 0;
		virtual void resize(double k) = 0;

		virtual void rotate(double dxy, double dyz, double dzx, const Point& center) = 0;
		virtual void resize(double k, const Point& center) = 0;
};

#endif // SCENEOBJECT_H
