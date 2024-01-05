#pragma once

#include "huffman_tree_node.h"
#include <queue>
#include <vector>

class HuffmanTree {
public:
	HuffmanTree(const std::vector<std::pair<char, double>>& frequencies);
	std::shared_ptr<HuffmanTreeNode> getRoot() const;
	void printTree() const;

private:
	std::shared_ptr<HuffmanTreeNode> root;
	void printTreeHelper(const std::string& prefix, const std::shared_ptr<HuffmanTreeNode>& node, bool isLeft) const;

	// Eigenen Vergleichsoperator für die Priority Queue
	struct Compare {
		bool operator()(const std::shared_ptr<HuffmanTreeNode>& a,
			const std::shared_ptr<HuffmanTreeNode>& b) const {
			return a->frequency > b->character;
		}
	};

};