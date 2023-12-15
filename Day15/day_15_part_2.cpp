#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>

int Get_Box_Idx(const std::string& line) {
	int result = 0;
	for (int i = 0; i < line.size(); i++) {
		result = ((line[i] + result) * 17) % 256;
	}
	return result;
}

int Find_Focusing_Power(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	std::string label;
	std::vector<std::string> input;
	std::unordered_map<std::string, std::list<int>::iterator> cache;
	std::vector<std::list<int>> boxes(256);
	int result = 0, idx = 0, box_idx = 0;
	
	std::getline(file, line);
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ',') {
			input.push_back(line.substr(idx, i - idx));
			idx = i + 1;
		}
	}
	input.push_back(line.substr(idx));

	for (int i = 0; i < input.size(); i++) {
		if (input[i].back() == '-') {
			label = input[i].substr(0, input[i].size() - 1);
			if (cache.find(label) != cache.end()) {
				box_idx = Get_Box_Idx(label);
				boxes[box_idx].erase(cache[label]);
				cache.erase(label);
			}
		}
		else {
			label = input[i].substr(0, input[i].size() - 2);
			if (cache.find(label) != cache.end()) {
				*(cache[label]) = input[i].back() - '0';
			}
			else {
				box_idx = Get_Box_Idx(label);
				boxes[box_idx].push_back(input[i].back() - '0');
				cache[label] = std::prev(boxes[box_idx].end());
			}
		}
	}

	for (int i = 0; i < boxes.size(); i++) {
		idx = 1;
		for (const int& element : boxes[i]) {
			result += (i + 1) * idx * element;
			idx++;
		}
	}

	return result;
}
