#pragma

#include "huffman_tree_node.h"
#include <queue>
#include <vector>
#include <map>

class HuffmanTree {
public:
	HuffmanTree(const std::vector<std::pair<char, double>>& frequencies);
	std::shared_ptr<HuffmanTreeNode> getRoot() const;
	void printTree() const;

	std::map<char, std::string> createEncodingTable() const;

	std::string encodeText(const std::string& text, bool printStats = false) const;

	std::string decodeText(const std::string& encodedText) const;

private:
	std::shared_ptr<HuffmanTreeNode> root;
	void printTreeHelper(const std::string& prefix, const std::shared_ptr<HuffmanTreeNode>& node, bool isLeft) const;

	void createEncodingTableHelper(const std::shared_ptr<HuffmanTreeNode>& node,
		std::string code,
		std::map<char, std::string>& encodingTable) const;

	mutable std::map<char, std::string> encodingTable;
	void buildEncodingTable() const;

	// Eigenen Vergleichsoperator für die Priority Queue
	struct Compare {
		bool operator()(const std::shared_ptr<HuffmanTreeNode>& a,
			const std::shared_ptr<HuffmanTreeNode>& b) const {
			return a->frequency > b->frequency;
		}
	};

};
