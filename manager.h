#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "prism.h"
#include "light.h"
#include "camera.h"

const Point p_c(0, 0, 400);
const Point p_d(0, 0, -1);
const double distance = 300;

class Manager
{
	public:

		Manager();

		void add_prism(Prism& prism);
		void del_prism(int index);

		void add_light(Light& light);
		void del_light(int index);

		int number_of_prism();
		int number_of_light();
		bool light_full();

		bool check_visible(Prism& prism);
		bool check_visible(Light& light);

		std::vector<Prism> prism_list;
		std::vector<Light> light_list;

		SceneObject* active_object = nullptr;

		Camera camera;

	private:
		unsigned prism_number;
		unsigned light_number;

};

#endif // MANAGER_H
