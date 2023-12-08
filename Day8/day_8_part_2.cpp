#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

long long GCD(long long a, long long b) {

	long long temp = 0;
	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

long long LCM(long long a, long long b) {

	if (a == 0 || b == 0) return 0;
	
	return (a * b) / GCD(a, b);
}

long long Find_End_Point_All_Nodes(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::string directions;
	std::vector<std::string> nodes;
	std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
	long long result = 0;
	int idx = 0;
	int valid_idx = 0;

	std::getline(file, directions);
	std::getline(file, current_line);

	while (std::getline(file, current_line)) {
		graph[current_line.substr(0, 3)] = { current_line.substr(7,3), current_line.substr(12, 3) };

		if (current_line[2] == 'A') {
			nodes.push_back(current_line.substr(0, 3));
		}
	}

	for (int i = 0; i < nodes.size(); i++) {

		idx = 0;
		while (nodes[i].back() != 'Z'){
			nodes[i] = (directions[idx % directions.length()] == 'L') ? graph[nodes[i]].first : graph[nodes[i]].second;
			idx++;
		}
		result = (result == 0) ? idx : LCM(result, idx);
	}
	
	return result;
}
