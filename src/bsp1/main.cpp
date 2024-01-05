#include "frequency_table.h"
#include "huffman_tree.h"
#include <iostream>

int main () {
	// Datei öffnen, Frequenzen berechnen und ausgeben
	FrequencyTable table;
	table.readFile("Text6.txt");
	table.calculateFrequencies();
	table.printTable();

	// Huffman Baum
	HuffmanTree tree(table.getFrequencies());
	auto root = tree.getRoot();
	tree.printTree();

	// Coding Table
	auto encodingTable = tree.createEncodingTable();
	for (const auto& pair : encodingTable) {
		std::cout << "'" << pair.first << "': " << pair.second << "\n";
	}

	std::string text = table.getText();
	std::string encodedText = tree.encodeText(text, true);
	std::cout << "Kodierter Text: " << encodedText << "\n\n";
	std::string decodedText = tree.decodeText(encodedText);
	std::cout << "Entkodierter Text: " << decodedText << "\n\n";
	if (text == decodedText) {
		std::cout << "Der dekodierte Text stimmt mit dem originalen Text ueberein." << std::endl;
	}
	else {
		std::cout << "Der dekodierte Text stimmt NICHT mit dem originalen Text ueberein." << std::endl;
	}
}
