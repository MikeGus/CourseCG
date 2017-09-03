#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

class SceneObject {
	public:
		virtual void move(float dx, float dy, float dz) = 0;
		virtual void rotate(float dxy, float dyz, float dzx) = 0;
		virtual void resize(float k) = 0;
};

#endif // SCENEOBJECT_H
