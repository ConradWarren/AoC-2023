#include <fstream>
#include <iostream>
#include <string>

int Find_Spelled_Out_Digits(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<std::string> patterns_to_match = { "one", "two","three","four", "five","six", "seven", "eight","nine" };
	int first_digit = 0;
	int last_digit = 0;
	long long result = 0;
	int idx = 0;
	
	if (!file.is_open()) {
		std::cout << "Error: Could not open file\n";
		return -1;
	}

	while (std::getline(file, current_line)){
		
		first_digit = -1;
		last_digit = -1;

		for (int i = 0; i < current_line.length(); i++) {
			
			if (current_line[i] - '0' > 0 && current_line[i] - '0' < 10) {
				first_digit = (first_digit == -1) ? current_line[i] - '0' : first_digit;
				last_digit = current_line[i] - '0';
				continue;
			}

			for (int j = 0; j < patterns_to_match.size(); j++) {

				if (current_line.substr(i, patterns_to_match[j].length()) == patterns_to_match[j]) {
					first_digit = (first_digit == -1) ? j + 1 : first_digit;
					last_digit = j + 1;
					break;
				}
			}
		}

		if (first_digit < 0 || last_digit < 0) {
			std::cout << "Error: could not find digit\n";
			return -1;
		}

		result += (first_digit * 10) + last_digit;

	}

	return result;
}
