#ifndef BEAM_TREE_H
#define BEAM_TREE_H

#include <vector>
#include "beam.h"
#include <QColor>
#include "light.h"
#include "edge.h"

const unsigned max_level = 5;

class BeamTreeNode {

	public:
		Beam beam;
		unsigned level;
		bool is_light;

		Prism* prism;
		Edge edge;
		Light* light;

		BeamTreeNode* parent;
		BeamTreeNode* reflect;
		BeamTreeNode* refract;

		BeamTreeNode();
		BeamTreeNode(Beam& beam, unsigned level, bool is_light, Prism* prism, Edge& edge, Light* light,
					 BeamTreeNode* parent);

		~BeamTreeNode();
};

class BeamTree {
	public:
		BeamTreeNode* root;
		BeamTree(Beam& original, Prism* prism, Edge& edge);

		~BeamTree();

		void calculate_tree(BeamTreeNode* node, std::vector<Prism>& prism_list, std::vector<Light>& light_list);
		void calculate_color(std::vector<Light>& light_list, std::vector<Prism>& prism_list, BeamTreeNode* node,
									   QColor& color);
};


#endif // BEAM_TREE_H
