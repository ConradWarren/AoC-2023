#include <fstream>
#include <string>

int Solve_Number_of_Ways_2(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	long long time = 0;
	long long distance = 0;
	int result = 0;

	std::getline(file, current_line);

	for (int i = 5; i < current_line.length(); i++) {
		if (current_line[i] != ' ') {
			time = (time * 10) + current_line[i] - '0';
		}
	}

	std::getline(file, current_line);

	for (int i = 9; i < current_line.length(); i++) {
		if (current_line[i] != ' ') {
			distance = (distance * 10) + current_line[i] - '0';
		}
	}

	for (int i = 1; i < time; i++) {
		result = (i * (time - i)) ? result + 1 : result;
	}

	return result;
}
