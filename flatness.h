#ifndef FLATNESS_H
#define FLATNESS_H

class Point;

class Flatness
{
	public:
		Flatness(float A=0, float B=0, float C=0, float D=0);

		bool in_flatness(Point& check, float acc=1e-4);

		float a;
		float b;
		float c;
		float d;
};

#endif // FLATNESS_H
