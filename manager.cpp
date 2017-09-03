#include "manager.h"

Manager::Manager(): active_object(nullptr), camera(p_c, p_d), prism_number(1), light_number(1){}

void Manager::add_prism(Prism &prism)
{
	++prism_number;
	prism_list.push_back(prism);
}

void Manager::del_prism(int index)
{
	for (int i = index; i < (int)prism_list.size() - 1; ++i) {
		prism_list[i] = prism_list[i + 1];
	}
	prism_list.pop_back();
}

int Manager::number_of_prism()
{
	return prism_number;
}

int Manager::number_of_light()
{
	return light_number;
}

bool Manager::light_full()
{
	return light_list.size() >= 3;
}

void Manager::add_light(Light& light)
{
	++light_number;
	light_list.push_back(light);
}

void Manager::del_light(int index)
{
	for (int i = index; i < (int)light_list.size() - 1; ++i) {
		light_list[i] = light_list[i + 1];
	}
	light_list.pop_back();
}

bool Manager::check_visible(Prism& prism)
{
	for (Edge& ed : prism.top_edges) {
		for (Point& p : ed.points) {
			if (!camera.point_visible(p)) {
				return false;
			}
		}
	}
	return true;
}


bool Manager::check_visible(Light& light)
{
	return camera.point_visible(light.coordinates);
}
