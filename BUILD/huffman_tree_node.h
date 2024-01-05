#pragma once

#include <memory>

class HuffmanTreeNode {
public:
	char character;
	double frequency;
	std::shared_ptr<HuffmanTreeNode> left;
	std::shared_ptr<HuffmanTreeNode> right;

	HuffmanTreeNode(char ch, double freq)
		: character(ch), frequency(freq), left(nullptr), right(nullptr) {}

	// Vergleichsoperator für die Prioritätswarteschlange
	bool operator>(const HuffmanTreeNode& other) const {
		return frequency > other.frequency;
	}
};