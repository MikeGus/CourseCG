#ifndef UTILS_H
#define UTILS_H

#include <QColor>

class Prism;
class Light;
class Point;
class Edge;

void change_color(QColor& changed_color, QColor& addition, const double reflection_coefficient,
				  const double distance);

void calculate_diff(std::vector<Light>& light_list, std::vector<Prism>& prism_list,
						  Point& cross_point_nearest, Edge& cross_edge_nearest, Prism& cross_prism_nearest, QColor& color);

#endif // UTILS_H
