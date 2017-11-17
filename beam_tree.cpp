#include "beam_tree.h"
#include "beam.h"
#include "prism.h"
#include "light.h"
#include "utils.h"

BeamTreeNode::BeamTreeNode():level(0), is_light(false), prism(nullptr), light(nullptr), parent(nullptr),
	reflect(nullptr), refract(nullptr) {}

BeamTreeNode::BeamTreeNode(Beam& beam, unsigned level, bool is_light, Prism* prism, Edge& edge, Light* light,
						   BeamTreeNode* parent): beam(beam),
	level(level), is_light(is_light), prism(prism), edge(edge), light(light), parent(parent), reflect(nullptr),
	refract(nullptr) {}

BeamTreeNode::~BeamTreeNode() {
	if (reflect != nullptr) {
		delete reflect;
	}
	if (refract != nullptr) {
		delete refract;
	}
}

BeamTree::BeamTree(Beam& original, Prism* prism, Edge& edge) {
	root = new BeamTreeNode(original, 0, false, prism, edge, nullptr, nullptr);
}

BeamTree::~BeamTree() {
	delete root;
}

void BeamTree::calculate_tree(BeamTreeNode* node, std::vector<Prism>& prism_list, std::vector<Light>& light_list) {

	if ((node == nullptr) || (node->level >= max_level) || node->is_light || (node->prism == nullptr)) {
		return;
	}

	if (node->prism->reflect > 0) {
		Beam reflected_beam(node->beam.reflected(node->edge.flatness));
		Prism* reflected_prism = nullptr;
		Edge reflected_edge;
		Point cross_point;
		bool got_intersection = false;


		for (Prism& prism : prism_list) {
			if (reflected_beam.cross_prism(prism, cross_point, reflected_edge,
										   got_intersection)) {
				reflected_prism = &prism;
			}
		}

		bool is_light = false;
		Light* cross_light = nullptr;
		for (Light& light : light_list) {
			if (reflected_beam.cross_light(light)) {
				Point cross_point_light(reflected_beam.cross_light_point(light));
				if (!got_intersection
						|| (reflected_beam.p1.distance(cross_point_light) < reflected_beam.p1.distance(cross_point))) {
					got_intersection = true;
					is_light = true;
					cross_point = cross_point_light;
					cross_light = &light;
				}
			}
		}

		if (got_intersection) {
			reflected_beam.p2 = cross_point;
			node->reflect = new BeamTreeNode(reflected_beam, node->level + 1, is_light, reflected_prism, reflected_edge,
											 cross_light, node);
			calculate_tree(node->reflect, prism_list, light_list);
		}


	}

	if (node->prism->refract > 0) {
		Beam refracted_beam(node->beam.refracted(node->edge.flatness, node->prism->refract));

		if (refracted_beam.length() > 0) {

			Prism* refracted_prism = nullptr;
			Edge refracted_edge;
			Point cross_point;
			bool got_intersection = false;

			for (Prism& prism : prism_list) {
				if (refracted_beam.cross_prism(prism, cross_point, refracted_edge, got_intersection)) {
					refracted_prism = &prism;
				}
			}

			bool is_light = false;
			Light* cross_light = nullptr;
			for (Light& light : light_list) {
				if (refracted_beam.cross_light(light)) {
					Point cross_point_light(refracted_beam.cross_light_point(light));
					if (!got_intersection
							|| (refracted_beam.p1.distance(cross_point_light) < refracted_beam.p1.distance(cross_point))) {
						got_intersection = true;
						is_light = true;
						cross_point = cross_point_light;
						cross_light = &light;
					}
				}
			}

			if (got_intersection) {
				refracted_beam.p2 = cross_point;

				node->refract = new BeamTreeNode(refracted_beam, node->level + 1, is_light, refracted_prism, refracted_edge,
												 cross_light, node);

				calculate_tree(node->refract, prism_list, light_list);
			}
		}
	}
}

void BeamTree::calculate_color(std::vector<Light>& light_list, std::vector<Prism>& prism_list, BeamTreeNode* node,
							   QColor& color) {

	if (node == nullptr || (node->prism == nullptr && node->light == nullptr)) {
		return;
	}

	if (node->reflect != nullptr) {
		QColor new_color;
		calculate_color(light_list, prism_list, node->reflect, new_color);
		color.setRedF(color.redF() + new_color.redF() * node->prism->reflect);
		color.setGreenF(color.greenF() + new_color.greenF() * node->prism->reflect);
		color.setBlueF(color.blueF() + new_color.blueF() * node->prism->reflect);
	}
	if (node->refract != nullptr) {
		QColor new_color;
		calculate_color(light_list, prism_list, node->refract, new_color);
		color.setRedF(color.redF() + new_color.redF() * node->prism->refract);
		color.setGreenF(color.greenF() + new_color.greenF() * node->prism->refract);
		color.setBlueF(color.blueF() + new_color.blueF() * node->prism->refract);
	}

	if (node->is_light) {
		color.setRedF(node->light->intensity.redF() + color.redF());
		color.setGreenF(node->light->intensity.greenF() + color.greenF());
		color.setBlueF(node->light->intensity.blueF() + color.blueF());
	} else {
		calculate_diff(light_list, prism_list, node->beam.p2, node->edge, *(node->prism), color);
	}
}
