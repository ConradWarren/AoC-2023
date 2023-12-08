#include <fstream>
#include <string>
#include <unordered_map>

int Find_End_Point(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::string directions;
	std::string node = "AAA";
	std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
	int result = 0;
		
	std::getline(file, directions);
	std::getline(file, current_line);

	while (std::getline(file, current_line)){
		graph[current_line.substr(0, 3)] = { current_line.substr(7,3), current_line.substr(12, 3) };
	}

	while (node != "ZZZ"){
		node = (directions[result % directions.length()] == 'L') ? graph[node].first : graph[node].second;
		result++;
	}

	return result;
}
