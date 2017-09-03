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
			if (i > 0 && points[i].x != points[i - 1].x && points[i].y != points[i - 1].y && points[i].z != points[i - 1].z) {
				matrix[i][0] = points[i].x;
				matrix[i][1] = points[i].y;
				matrix[i][2] = points[i].z;
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
			Point main_vec((*it_2).x - (*it_1).x, (*it_2).y - (*it_1).y, (*it_2).z - (*it_1).z);
			Point sub_vec(check.x - (*it_1).x, check.y - (*it_1).y, check.z - (*it_1).z);

			last = current;
			current = main_vec.x * sub_vec.x + main_vec.y * sub_vec.y + main_vec.z * sub_vec.z;

			if (current * last < 0) {
				return false;
			}
		}
	}

	return (current < 0);
}
