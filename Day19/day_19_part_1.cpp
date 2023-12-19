#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

class part {

public:
	part(const std::string& input) {
		values.resize(4);
		int last_valid_idx = -1;
		int idx = 0;
		for (int i = 1; i < input.size(); i++) {
			if (input[i] == '=') {
				last_valid_idx = i + 1;
			}
			else if (input[i] == ',' || input[i] == '}') {
				values[idx] = std::stoi(input.substr(last_valid_idx, i - last_valid_idx + 1));
				idx++;
			}
		}
	}
	std::vector<int> values;
};

class workflow {

public:

	workflow(const std::string& input) {

		int idx = input.length() - 2;
		int last_valid_idx = 0;
		while (idx >= 0 && input[idx] != ',') {
			idx--;
		}
		else_state = input.substr(idx + 1, input.length() - idx - 1);

		for (int i = 0; i <= idx; i++) {
			if (input[i] == ',') {
				Parse(input.substr(last_valid_idx, i - last_valid_idx));
				last_valid_idx = i + 1;
			}
		}
	}

	void Parse(const std::string& input) {

		is_greater.push_back((input[1] == '>'));

		int current_num = 0;
		int idx = 2;
		while (input[idx] != ':') {
			current_num *= 10;
			current_num += input[idx] - '0';
			idx++;
		}
		val_keys.push_back({ val_map[input[0]], current_num });
		passes.push_back(input.substr(idx + 1));
	}

	std::string Compare(part& input_part) {

		for (int i = 0; i < is_greater.size(); i++) {
			if ((is_greater[i] && input_part.values[val_keys[i].first] > val_keys[i].second) || (!is_greater[i] && input_part.values[val_keys[i].first] < val_keys[i].second)) {
				return passes[i];
			}
		}

		return else_state;
	}

	std::vector<bool> is_greater;
	std::vector<std::pair<int, int>> val_keys;
	std::vector<std::string> passes;
	std::string else_state;
	std::unordered_map<char, int> val_map = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };
};


int Find_Part_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	std::unordered_map<std::string, workflow*> workflow_map;
	int idx = 0;
	int result = 0;

	while (std::getline(file, line) && !line.empty()) {

		idx = 0;
		while (idx < line.length() && line[idx] != '{') {
			idx++;
		}
		workflow_map[line.substr(0, idx)] = new workflow(line.substr(idx + 1, line.length() - idx - 2));
	}

	while (std::getline(file, line)) {

		part _part(line);
		std::string workflow_output = "in";

		while (workflow_output != "A" && workflow_output != "R") {
			workflow_output = workflow_map[workflow_output]->Compare(_part);
		}

		if (workflow_output == "R") {
			continue;
		}

		for (int i = 0; i < _part.values.size(); i++) {
			result += _part.values[i];
		}
	}

	for (auto& _workflow : workflow_map) {
		delete _workflow.second;
	}

	return result;
}
