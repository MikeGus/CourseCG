#include "edge.h"
#include "point.h"
#include "flatness.h"
#include <cmath>
#include <vector>
#include <stdexcept>

const int PTNUM = 3;
const int COEFNUM = 4;
const double ACC = 1e-4;

void Edge::setup_flatness()
{
	Flatness result;

	std::vector<Point> base;
	for (unsigned i = 0; i < PTNUM; ++i) {
		base.push_back(points[i]);
	}

	if (base.size() < PTNUM) {
		throw std::logic_error("Invalid edge!");
	}


	base[1] -= base[0];
	base[2] -= base[0];

	result.a = base[1].get_y() * base[2].get_z() - base[1].get_z() * base[2].get_y();
	result.b = base[1].get_z() * base[2].get_x() - base[1].get_x() * base[2].get_z();
	result.c = base[1].get_x() * base[2].get_y() - base[1].get_y() * base[2].get_x();

	result.d = - (base[0].get_x() * result.a + base[0].get_y() * result.b + \
			base[0].get_z() * result.c);

	flatness = result;
}

bool Edge::in_edge(const Point& check, double acc) const
{

	bool in_flat = flatness.in_flatness(check, acc);
	if (!in_flat) {
		return false;
	}

	std::vector<Point> point_vec = points;
	point_vec.push_back(*points.begin());

	Point current(0, 0, 0);
	Point last(0, 0, 0);

	bool first = true;

	auto it_1 = point_vec.begin();
	for (auto it_2 = it_1 + 1; it_2 < point_vec.end(); ++it_1, ++it_2) {
		Point main_vec(*it_2 - *it_1);
		Point sub_vec(check - *it_1);

		last = current;

		current.set_x(main_vec.get_y() * sub_vec.get_z() - main_vec.get_z() * sub_vec.get_y());
		current.set_y(main_vec.get_z() * sub_vec.get_x() - main_vec.get_x() * sub_vec.get_z());
		current.set_z(main_vec.get_y() * sub_vec.get_z() - main_vec.get_z() * sub_vec.get_y());

		if (!first) {
			double scalar = current.get_x() * last.get_x() + \
					current.get_y() * last.get_y() + current.get_z() * last.get_z();
			if (scalar <= 0) {
				return false;
			}
		}
		first = false;
	}

	return true;
}


bool Edge::operator==(const Edge& other) const {
	auto this_it = points.cbegin();
	for (auto other_it = other.points.cbegin(); this_it != points.cend() && other_it != other.points.cend(); ++this_it, ++other_it) {
		if (*this_it != *other_it) {
			return false;
		}
	}
	return true;
}
