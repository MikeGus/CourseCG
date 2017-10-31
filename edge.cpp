#include "edge.h"
#include "point.h"
#include "flatness.h"
#include <cmath>
#include <vector>

const int PTNUM = 3;
const int COEFNUM = 4;
const float ACC = 1e-4;

Flatness Edge::egde_flatness()
{
	Flatness result;

	if (points.size() >= PTNUM) {
		result.d = 1;

		std::vector<std::vector<float>> matrix;
		matrix.resize(COEFNUM);
		for (auto& el : matrix) {
			el.resize(PTNUM);
		}

		for (int i = 0; i < 3; ++i) {
			if (i > 0 && points[i].get_x() != points[i - 1].get_x() && \
					points[i].get_y() != points[i - 1].get_y() && \
					points[i].get_z() != points[i - 1].get_z()) {

				matrix[i][0] = points[i].get_x();
				matrix[i][1] = points[i].get_y();
				matrix[i][2] = points[i].get_z();
				matrix[i][3] = 1;
			}
		}

		for (int i = 0; i < PTNUM; ++i) {
			if (fabs(matrix[i][i]) < ACC) {
				for (int j = i + 1; j < PTNUM; ++j) {
					if (fabs(matrix[j][i]) > ACC) {
						std::swap(matrix[i], matrix[j]);
					}
				}
			}

			for (int j = i + 1; j < PTNUM; ++j) {
				float mult = matrix[j][i] / matrix[i][i];

				for (int k = i; k < COEFNUM; ++k) {
					matrix[j][k] -= matrix[i][k] * mult;
				}
			}

			std::vector<float> results;

			results.resize(4,0);
			results[3] = 1;

			for (int j = PTNUM - 1; j >= 0; --j) {
				float sum = 0;
				for (int k = j + 1; k < COEFNUM; ++k) {
					sum += (matrix[j][k] * results[k]);
				}

				sum *= -1;
				results[j] = sum / matrix[j][j];
			}

			result.a = results[0];
			result.b = results[1];
			result.c = results[2];
			result.d = results[3];
		}
	}

	return result;
}

bool Edge::in_edge(Point& check, float acc)
{
	Flatness ed_flat = egde_flatness();

	bool in_flat = ed_flat.in_flatness(check, acc);
	if (!in_flat) {
		return false;
	}

	std::vector<Point> point_vec = points;
	point_vec.push_back(*points.cend());

	float current = 0;
	float last = 0;

	for (auto it_1 = point_vec.begin(); it_1 < point_vec.end() - 1; ++it_1) {
		for (auto it_2 = it_1 + 1; it_2 < point_vec.end(); ++it_2) {
			Point main_vec((*it_2).get_x() - (*it_1).get_x(),
						   (*it_2).get_y() - (*it_1).get_y(),
						   (*it_2).get_z() - (*it_1).get_z());

			Point sub_vec(check.get_x() - (*it_1).get_x(),
						  check.get_y() - (*it_1).get_y(),
						  check.get_z() - (*it_1).get_z());

			last = current;
			current = main_vec.get_x() * sub_vec.get_x() + \
					main_vec.get_y() * sub_vec.get_y() + \
					main_vec.get_z() * sub_vec.get_z();

			if (current * last < 0) {
				return false;
			}
		}
	}

	return (current < 0);
}
