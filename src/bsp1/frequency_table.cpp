#include "frequency_table.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

void FrequencyTable::readFile(const std::string& filename) {
	std::ifstream file(filename);
	char c;

	std::cout << "Geoeffnete Datei:\n";
	while (file >> std::noskipws >> c)
	{
		frequencyMap[c]++;
		totalChars++;
		std::cout << c;
		text += c;
	}
	if (totalChars == 0)
	{
		std::cerr << "FEHLER: Textdatei ist leer.";
		EXIT_FAILURE;
	}

	std::cout << "\n\n";
}

void FrequencyTable::calculateFrequencies() {
	for (const auto& pair : frequencyMap) {
		frequencies.emplace_back(pair.first, static_cast<double>(pair.second) / totalChars * 100);
	}

	// Sortieren der Frequenzen
	std::sort(frequencies.begin(), frequencies.end(),
		[](const std::pair<char, double>& a, const std::pair<char, double>& b) {
			return a.second > b.second; // Sortiere absteigend
		});
}

void FrequencyTable::printTable() const {
	std::cout << "Zeichen | Relative Häufigkeit (%)\n";
	std::cout << "---------------------------------\n";
	if (!frequencies.empty()) {
		for (const auto& pair : frequencies)
		{
			std::cout << "   " << pair.first << "    | " << pair.second << "\n";
		}
	}
}