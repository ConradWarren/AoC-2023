int Find_Winning_Numbers(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::unordered_set<int> nums_to_match;
	int current_num = 0;
	int idx = 0;
	int current_point = 0;
	int result = 0;

	while (std::getline(file, current_line)){

		idx = 0;

		while (idx < current_line.length() && current_line[idx] != ':'){
			idx++;
		}

		idx++;

		nums_to_match.clear();

		while (idx < current_line.length() && current_line[idx] != '|'){

			if (current_line[idx] == ' ' && current_num == 0) {
				idx++;
				continue;
			}
			if (current_line[idx] == ' ') {
				nums_to_match.insert(current_num);
				current_num = 0;
			}
			else {
				current_num *= 10;
				current_num += current_line[idx] - '0';
			}

			idx++;
		}

		if (current_num != 0) {
			nums_to_match.insert(current_num);
			current_num = 0;
		}

		idx++;
		current_point = 0;

		while (idx< current_line.length()){

			if (current_line[idx] == ' ' && current_num == 0) {
				idx++;
				continue;
			}
			if (current_line[idx] == ' ') {
				if (nums_to_match.find(current_num) != nums_to_match.end()) {
					current_point = (current_point == 0) ? 1 : current_point * 2;
				}
				current_num = 0;
			}
			else {
				current_num *= 10;
				current_num += current_line[idx] - '0';
			}
			idx++;
		}

		if (current_num != 0 && nums_to_match.find(current_num) != nums_to_match.end()) {
			current_point = (current_point == 0) ? 1 : current_point * 2;
		}
		
		current_num = 0;

		result += current_point;
	}

	return result;
}
