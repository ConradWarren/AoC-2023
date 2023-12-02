#include <string>
#include <fstream>

int Find_Power_of_Set(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	int count = 0;
	int result = 0;
	int idx = 0;
	int red_max = 0;
	int blue_max = 0;
	int green_max = 0;

	while (std::getline(file, current_line)) {

		idx = 0;

		while (idx < current_line.length() && current_line[idx] != ':') idx++;
		
		idx++;

		red_max = 0;
		blue_max = 0;
		green_max = 0;

		while (idx < current_line.length()) {

			while (idx < current_line.length() && (current_line[idx] < '0' || current_line[idx] > '9')) idx++;
		
			count = 0;

			while (idx < current_line.length() && current_line[idx] != ' ') {
				count *= 10;
				count += current_line[idx] - '0';
				idx++;
			}

			while (idx < current_line.length() && current_line[idx] == ' ') idx++;
			
			if (current_line.substr(idx, 3) == "red") red_max = (red_max > count) ? red_max : count;
			
			else if (current_line.substr(idx, 5) == "green") green_max = (green_max > count) ? green_max : count;
			
			else if (current_line.substr(idx, 4) == "blue") blue_max = (blue_max > count) ? blue_max : count;
		}
		result += (red_max * blue_max * green_max);
	}

	return result;
}
