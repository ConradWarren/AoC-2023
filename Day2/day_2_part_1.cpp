#include <string>
#include <fstream>

int Find_Valid_Games(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	int id = 1;
	int count = 0;
	int result = 0;
	int idx = 0;

	while (std::getline(file, current_line)){
		
		idx = 0;

		while (idx < current_line.length() && current_line[idx] != ':') idx++;
		
		idx++;
		
		while (idx < current_line.length()){

			while (idx < current_line.length() && (current_line[idx] < '0' || current_line[idx] > '9')) idx++;
			
			count = 0;

			while (idx < current_line.length() && current_line[idx] != ' '){
				count *= 10;
				count += current_line[idx] - '0';
				idx++;
			}

			while (idx < current_line.length() && current_line[idx] == ' ')idx++;
			
			if (current_line.substr(idx, 3) == "red" && count > 12) {
				result -= id;
				break;
			}
			else if (current_line.substr(idx, 5) == "green" && count > 13) {
				result -= id;
				break;
			}
			else if (current_line.substr(idx, 4) == "blue" && count > 14) {
				result -= id;
				break;
			}
		}
		result += id;
		id++;
	}

	return result;
}
