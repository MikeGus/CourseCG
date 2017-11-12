#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include <QColor>
#include "sceneobject.h"

class Light : public SceneObject {
	public:
		Light() = default;
		Light(Point& coordinates, QColor intensity=QColor("white"));

		Point coordinates;
		QColor intensity;

		void move(double dx, double dy, double dz);

		void rotate(double dxy, double dyz, double dzx);
		void resize(double k);

		void rotate(double dxy, double dyz, double dzx, const Point& center);
		void resize(double k, const Point& center);
};

#endif // LIGHT_H
