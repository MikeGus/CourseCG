#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include <QColor>
#include "sceneobject.h"

class Light : public SceneObject {
	public:
		Light(Point& coordinates, QColor intensity=QColor("white"));

		Point coordinates;
		QColor intensity;

		void move(float dx, float dy, float dz);
		void rotate(float dxy, float dyz, float dzx);
		void resize(float k);
};

#endif // LIGHT_H
