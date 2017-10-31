#ifndef POINT_H
#define POINT_H

class Point
{
	public:
		Point(const float x=0, const float y=0, const float z=0);

		float distance(const Point& other);

		float get_dx(const Point& other) const;
		float get_dy(const Point& other) const;
		float get_dz(const Point& other) const;

		void set_x(const float x);
		void set_y(const float y);
		void set_z(const float z);

		float get_x() const;
		float get_y() const;
		float get_z() const;

		Point operator*(const float k);
		Point& operator*=(const float k);

		Point& operator+=(const Point& other);
		Point& operator-=(const Point& other);

		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;

		void rotate_dxy(const float dxy, const Point& center);
		void rotate_dyz(const float dyz, const Point& center);
		void rotate_dzx(const float dzx, const Point& center);

	private:
		float x;
		float y;
		float z;

};

#endif // POINT_H
