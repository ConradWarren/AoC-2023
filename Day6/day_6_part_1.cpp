#include <fstream>
#include <string>
#include <vector>

int Solve_Number_of_Ways(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<int> times;
	std::vector<int> distances;
	int current_num = 0;
	int result = 0;
	int current_ways = 0;

	std::getline(file, current_line);

	for (int i = 5; i < current_line.length(); i++) {

		if (current_line[i] == ' ' && current_num == 0) continue;
	
		if (current_line[i] != ' ') {
			current_num = (current_num * 10) + current_line[i] - '0';
		}
		else {
			times.push_back(current_num);
			current_num = 0;
		}
	}

	if (current_num != 0) {
		times.push_back(current_num);
		current_num = 0;
	}

	std::getline(file, current_line);
	
	for (int i = 9; i < current_line.length(); i++) {

		if (current_line[i] == ' ' && current_num == 0) {
			continue;
		}

		if (current_line[i] != ' ') {
			current_num = (current_num * 10) + current_line[i] - '0';
		}
		else {
			distances.push_back(current_num);
			current_num = 0;
		}
	}
	
	if (current_num != 0) {
		distances.push_back(current_num);
	}

	for (int i = 0; i < times.size(); i++) {
		current_ways = 0;
		for (int j = 1; j < times[i]; j++) {
			current_ways = (j * (times[i] - j)) ? current_ways + 1 : current_ways;
		}
		result = (result == 0) ? current_ways : result * current_ways;
	}

	return result;
}
