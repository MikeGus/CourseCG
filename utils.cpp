#include "utils.h"
#include "prism.h"
#include "light.h"
#include "point.h"
#include "edge.h"
#include "beam.h"

void change_color(QColor& changed_color, QColor& addition, const double reflection_coefficient,
				  const double distance) {

	double distance_factor = 0.5 + 100 / distance;
	distance_factor = (distance_factor > 1) ? 1 : distance_factor;

	double coefficient = distance_factor * reflection_coefficient;

	double value = changed_color.redF() + addition.redF() * coefficient;
	value = value > 1 ? 1 : value;
	changed_color.setRedF(value);


	value = changed_color.greenF() + addition.greenF() * coefficient;
	value = value > 1 ? 1 : value;
	changed_color.setGreenF(value);


	value = changed_color.blueF() + addition.blueF() * coefficient;
	value = value > 1 ? 1 : value;
	changed_color.setBlueF(value);
}

void calculate_diff(std::vector<Light>& light_list, std::vector<Prism>& prism_list,
						  Point& cross_point_nearest, Edge& cross_edge_nearest, Prism& cross_prism_nearest,
					QColor& color) {
	bool got_intersection = true;
	for (Light& light : light_list) {
		Beam light_beam(light.coordinates, cross_point_nearest);
		Point buffer_cross_point(cross_point_nearest);
		Edge buffer_cross_edge(cross_edge_nearest);

		bool changed = false;

		for (const Prism& prism : prism_list) {
			if (light_beam.cross_prism_with_check(prism, buffer_cross_point, buffer_cross_edge, got_intersection)) {
				if (!(buffer_cross_edge == cross_edge_nearest)) {
					changed = true;
					break;
				}
			}
		}
		if (!changed) {
			double angle = light_beam.get_angle(cross_edge_nearest.flatness);
			change_color(color, light.intensity,
						 cross_prism_nearest.diff_reflect * fabs(cos(angle)),
						 light_beam.p1.distance(cross_point_nearest));
		}
	}
}
