#include "huffman_tree.h"
#include <iostream>

HuffmanTree::HuffmanTree(const std::vector<std::pair<char, double>>& frequencies) {
	// Priority Queue für die Knoten
	std::priority_queue<std::shared_ptr<HuffmanTreeNode>,
		std::vector<std::shared_ptr<HuffmanTreeNode>>,
		Compare> pq;

	// Blattknoten für jede Frequenz
	for (const auto& pair : frequencies) {
		pq.push(std::make_shared<HuffmanTreeNode>(pair.first, pair.second));
	}

	// Kombinieren der Knoten
	while (pq.size() > 1) {
		auto left = pq.top(); pq.pop();
		auto right = pq.top(); pq.pop();

		// Neue interne Knoten
		auto internalNode = std::make_shared<HuffmanTreeNode>(0, left->frequency + right->frequency);
		internalNode->left = left;
		internalNode->right = right;

		pq.push(internalNode);
	}

	// Root = verbleibende Knoten in der Queue
	root = pq.top();
}

std::shared_ptr<HuffmanTreeNode> HuffmanTree::getRoot() const {
	return root;
}

void HuffmanTree::createEncodingTableHelper(const std::shared_ptr<HuffmanTreeNode>& node,
	std::string code,
	std::map<char, std::string>& encodingTable) const {
	if (node != nullptr) {
		// Blattknoten -> Code hinzufügen
		if (!node->left && !node->right) {
			encodingTable[node->character] = code;
		}
		else {
			// Links "0", rechts "1"
			createEncodingTableHelper(node->left, code + "0", encodingTable);
			createEncodingTableHelper(node->right, code + "1", encodingTable);
		}
	}
}

std::map<char, std::string> HuffmanTree::createEncodingTable() const {
	std::map<char, std::string> encodingTable;
	createEncodingTableHelper(root, "", encodingTable);
	return encodingTable;
}

void HuffmanTree::buildEncodingTable() const {
	if (encodingTable.empty()) {
		createEncodingTableHelper(root, "", encodingTable);
	}
}

std::string HuffmanTree::encodeText(const std::string& text, bool printStats) const {
	buildEncodingTable();

	std::string encodedText;
	for (char c : text) {
		encodedText += encodingTable[c];
	}

	if (printStats) {
		int originalBits = text.length() * 8;
		int compressedBits = encodedText.length();
		double compressionRatio = 100.0 * compressedBits / originalBits;

		std::cout << "Original Text Length (Bits): " << originalBits << std::endl;
		std::cout << "Compressed Text Length (Bits): " << compressedBits << std::endl;
		std::cout << "Kompressionsrate: " << compressionRatio << "%" << std::endl;
	}

	return encodedText;
}

std::string HuffmanTree::decodeText(const std::string& encodedText) const {
	std::string decodedText;
	auto currentNode = root;

	for (char bit : encodedText) {
		if (bit == '0') {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}

		if (!currentNode->left && !currentNode->right) {
			decodedText += currentNode->character;
			currentNode = root;
		}
	}

	return decodedText;
}

void HuffmanTree::printTree() const {
	printTreeHelper("", root, false);
}

void HuffmanTree::printTreeHelper(const std::string& prefix, const std::shared_ptr<HuffmanTreeNode>& node, bool isLeft) const {
	if (node != nullptr) {
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "i--");

		// Wert des Knotens
		if (node->character != '\0') { // '\0' = interner Knoten
			std::cout << node->character << "(" << node->frequency << ")" << std::endl;
		}
		else {
			std::cout << "*" << "(" << node->frequency << ")" << std::endl;
		}

		// Rekursiv linken und rechen Teilbaum aufrufen
		printTreeHelper(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printTreeHelper(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}