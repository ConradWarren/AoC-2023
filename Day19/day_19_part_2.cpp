#include <string?
#include <fstream>
#include <vector>
#include <unordered_map>

class part {

public:

	part() {
		value_ranges = { {1, 4000}, {1, 4000}, {1, 4000},{1, 4000} };
	}
	
	std::vector<std::pair<int, int>> value_ranges;
};

class workflow {

public:

	workflow(const std::string& input) {

		int idx = input.length() - 2;
		int last_valid_idx = 0;
		while (idx >= 0 && input[idx] != ','){
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

	std::vector<bool> is_greater;
	std::vector<std::pair<int, int>> val_keys;
	std::vector<std::string> passes;
	std::string else_state;
	std::unordered_map<char, int> val_map = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };
};

long long Find_Valid_Ranges(const std::string& key, std::unordered_map<std::string, workflow*>& workflow_map, part& _part) {

	if (key == "A") {
		long long result = 1;
		for (int i = 0; i < _part.value_ranges.size(); i++) {
			result *= _part.value_ranges[i].second - _part.value_ranges[i].first + 1;
		}
		return result;
	}
	if (key == "R") {
		return 0LL;
	}

	workflow* _workflow = workflow_map[key];
	long long result = 0;
	for (int i = 0; i < _workflow->is_greater.size(); i++) {

		if (_workflow->is_greater[i] && _part.value_ranges[_workflow->val_keys[i].first].second > _workflow->val_keys[i].second) {
			part new_part = _part;
			new_part.value_ranges[_workflow->val_keys[i].first].first = (new_part.value_ranges[_workflow->val_keys[i].first].first > _workflow->val_keys[i].second + 1) ? new_part.value_ranges[_workflow->val_keys[i].first].first : _workflow->val_keys[i].second + 1;
			result += Find_Valid_Ranges(_workflow->passes[i], workflow_map, new_part);
			_part.value_ranges[_workflow->val_keys[i].first].second = _workflow->val_keys[i].second;
		}
		else if(!_workflow->is_greater[i] && _part.value_ranges[_workflow->val_keys[i].first].first < _workflow->val_keys[i].second) {
			part new_part = _part;
			new_part.value_ranges[_workflow->val_keys[i].first].second = (new_part.value_ranges[_workflow->val_keys[i].first].second < _workflow->val_keys[i].second - 1) ? new_part.value_ranges[_workflow->val_keys[i].first].second : _workflow->val_keys[i].second - 1;
			result += Find_Valid_Ranges(_workflow->passes[i], workflow_map, new_part);
			_part.value_ranges[_workflow->val_keys[i].first].first = _workflow->val_keys[i].second;
		}
	}

	result += Find_Valid_Ranges(_workflow->else_state, workflow_map, _part);

	return result;
}


long long Find_All_Ranges(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	std::unordered_map<std::string, workflow*> workflow_map;
	int idx = 0;
	long long result = 0;
	
	while (std::getline(file, line) && !line.empty()){
		idx = 0;
		while (idx < line.length() && line[idx] != '{'){
			idx++;
		}
		workflow_map[line.substr(0, idx)] = new workflow(line.substr(idx + 1, line.length() - idx - 2));
	}
	part _part;
	result = Find_Valid_Ranges("in", workflow_map, _part);

	for (const std::pair<std::string, workflow*>& map_pair : workflow_map) {
		delete map_pair.second;
	}

	return result;
}
