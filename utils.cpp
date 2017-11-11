#include "utils.h"


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
