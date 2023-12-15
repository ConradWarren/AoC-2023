#include <fstream>
#include <string>

int Find_Hash_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	int result = 0;
	int current = 0;

	std::getline(file, line);

	for (int i = 0; i < line.length(); i++) {
		
		if (line[i] == ',') {
			result += current;
			current = 0;
		}
		else {
			current = ((current + line[i]) * 17) % 256;
		}
	}

	result += current;

	return result;
}
