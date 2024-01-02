#include "frequency_table.h"
#include <iostream>

int main () {
	// Datei öffnen, Frequenzen berechnen und ausgeben
	FrequencyTable table;
	table.readFile("Text2.txt");
	table.calculateFrequencies();
	table.printTable();




}
