#include "point.h"
#include <cmath>


Point::Point(const float x, const float y, const float z): x(x), y(y), z(z){}


float Point::distance(const Point& other) {
	float dx = get_dx(other);
	float dy = get_dy(other);
	float dz = get_dz(other);

	return sqrtf(dx * dx + dy * dy + dz * dz);
}


float Point::get_dx(const Point& other) const {
	return other.x - x;
}

float Point::get_dy(const Point& other) const {
	return other.y - y;
}

float Point::get_dz(const Point& other) const {
	return other.z - z;
}

void Point::set_x(const float x) {
	this->x = x;
}

void Point::set_y(const float y) {
	this->y = y;
}

void Point::set_z(const float z) {
	this->z = z;
}

float Point::get_x() const {
	return x;
}

float Point::get_y() const {
	return y;
}

float Point::get_z() const {
	return z;
}

Point Point::operator*(const float k) {

	Point result(*this);

	result.x *= k;
	result.y *= k;
	result.z *= k;

	return result;
}

Point& Point::operator*=(const float k) {
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

Point& Point::operator+=(const Point& other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Point& Point::operator-=(const Point& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Point Point::operator+(const Point& other) const {
	Point result(*this);
	result += other;
	return result;
}

Point Point::operator-(const Point& other) const {
	Point result(*this);
	result -= other;
	return result;
}

void Point::rotate_dxy(const float dxy, const Point& center) {
	float dx = center.get_dx(*this);
	float dy = center.get_dy(*this);

	x = center.get_x() + dx * cos(dxy) + dy * sin(dxy);
	y = center.get_y() - dx * sin(dxy) + dy * cos(dxy);
}

void Point::rotate_dyz(const float dyz, const Point& center) {
	float dy = center.get_dy(*this);
	float dz = center.get_dz(*this);

	y = center.get_y() + dy * cos(dyz) + dz * sin(dyz);
	z = center.get_z() - dy * sin(dyz) + dz * cos(dyz);
}

void Point::rotate_dzx(const float dzx, const Point& center) {
	float dz = center.get_dz(*this);
	float dx = center.get_dx(*this);

	z = center.get_z() - dx * sin(dzx) + dz * cos(dzx);
	x = center.get_x() + dx * cos(dzx) + dz * sin(dzx);
}
