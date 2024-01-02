#include "frequency_table.h"
#include <iostream>
#include <filesystem>

int main () {
	// Datei �ffnen, Frequenzen berechnen und ausgeben
	FrequencyTable table;
	table.readFile("Text3.txt");
	table.calculateFrequencies();
	table.printTable();


	std::cout << std::filesystem::current_path().string() << std::endl;

}
