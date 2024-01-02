#include <map>
#include <string>
#include <vector>

class FrequencyTable {
public:
	void readFile(const std::string& filename);
	void calculateFrequencies();
	void printTable() const;
	const std::vector<std::pair<char, double>>& getFrequencies() const {
		return frequencies;
	}



private:
	std::map<char, int> frequencyMap;
	std::vector<std::pair<char, double>> frequencies;
	int totalChars{ 0 };
};