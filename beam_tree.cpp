#include "beam_tree.h"
#include "beam.h"
#include "prism.h"
#include "light.h"

BeamTreeNode::BeamTreeNode(): parent(nullptr), reflect(nullptr), refract(nullptr) {}

BeamTreeNode::BeamTreeNode(Beam& beam, BeamTreeNode* parent, BeamTreeNode* reflect, BeamTreeNode* refract):
	current_beam(beam), parent(parent), reflect(reflect), refract(refract) {}

BeamTree::BeamTree(Beam& root) {
	this->root = new BeamTreeNode(root, nullptr, nullptr, nullptr);
}

BeamTree::~BeamTree() {
	root->free_children_recursive();
	free(root);
}

void BeamTreeNode::free_children_recursive() {
	if (reflect) {
		reflect->free_children_recursive();
	}
	if (refract) {
		refract->free_children_recursive();
	}
}


void BeamTreeNode::calculate_children_recursive(const Flatness& flatness, const double k, const std::vector<Prism>& prism_vector,
												const std::vector<Light>& light_vector, unsigned level) {
	if (level > max_level) {
		return;
	}

	Beam reflected(current_beam.reflected(flatness));

	double coefficient = (level % 2) ? k : 1/k;
	Beam refracted(current_beam.refracted(flatness, coefficient));

}
