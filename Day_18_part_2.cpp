#include <fstream>
#include <string>
#include <unordered_map>

long long Find_Area(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	std::pair<int, int> direction;
	std::unordered_map<char, std::pair<int, int>> dir_map = { {'3', {-1, 0}}, {'1', {1, 0}}, {'0', {0, 1}}, {'2', {0, -1}} };
	int idx = 0;
	int distance = 0;
	int y = 0;
	int x = 0;
	long long perimeter = 0;
	long long area = 0;

	while (std::getline(file, line)){

		direction = dir_map [line[line.length() - 2]];
		
		idx = 2;
		while(idx < line.length() && line[idx] != '#') {
			idx++;
		}
		distance = std::stoi(line.substr(idx+1, 5), nullptr, 16);
		perimeter += distance;
		
		for (int i = 0; i < distance; i++) {
			area += x * (y + direction.first) - (x + direction.second) * y;
			y += direction.first;
			x += direction.second;
		}
	}

	return std::abs(area) / 2 - (perimeter / 2) + 1 + perimeter;
}
