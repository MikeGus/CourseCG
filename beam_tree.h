#ifndef BEAM_TREE_H
#define BEAM_TREE_H

#include <vector>
#include "beam.h"

class Light;
class Prism;
class Beam;

const unsigned max_level = 5;

class BeamTreeNode {
	public:
		Beam current_beam;

		BeamTreeNode* parent;
		BeamTreeNode* reflect;
		BeamTreeNode* refract;

		BeamTreeNode();
		BeamTreeNode(Beam& beam, BeamTreeNode* parent, BeamTreeNode* reflect, BeamTreeNode* refract);

		void free_children_recursive();
		void calculate_children_recursive(const Flatness& flatness, const double k, const std::vector<Prism>& prism_vector,
										  const std::vector<Light>& light_vector, unsigned level);
};

class BeamTree {
	public:
		BeamTreeNode* root;
		BeamTree(Beam& root);

		~BeamTree();

		void calculate_beam_map(const std::vector<Prism>& prism_list, const std::vector<Light>& light_list);
};


#endif // BEAM_TREE_H
