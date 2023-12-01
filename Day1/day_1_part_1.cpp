#include <iostream>
#include <fstream>
#include <string>

int Find_Digits(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	int first_num = 0;
	int last_num = 0;
	int result = 0;

	if (!file.is_open()) {
		std::cout << "Error: Could not open file\n";
		return -1;
	}

	while (std::getline(file, current_line)){

		first_num = -1;
		last_num = -1;

		for (int i = 0; i < current_line.size(); i++) {
			
			if (current_line[i] - '0' < 0 || current_line[i] - '0' > 9) {
				continue;
			}

			if (first_num == -1) {
				first_num = current_line[i] - '0';
			}

			last_num = current_line[i] - '0';
		}

		if (first_num < 0 || last_num < 0) {
			std::cout << "Error: Could not find digit\n";
			return -1;
		}

		result += (first_num * 10) + last_num;
	}

	return result;
}
