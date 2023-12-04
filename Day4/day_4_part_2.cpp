int Fint_Number_of_Cards(const std::string input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::unordered_set<int> nums_to_match;
	std::unordered_map<int, int> card_counts;
	int current_num = 0;
	int id = 0;
	int idx = 0;
	int current_matches = 0;
	int result = 0;

	while (std::getline(file, current_line)) {

		idx = 0;
		id++;
		card_counts[id]++;

		while (idx < current_line.length() && current_line[idx] != ':') idx++;
		
		idx++;

		nums_to_match.clear();

		while (idx < current_line.length() && current_line[idx] != '|') {

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
		current_matches = 0;

		while (idx < current_line.length()) {

			if (current_line[idx] == ' ' && current_num == 0) {
				idx++;
				continue;
			}
			if (current_line[idx] == ' ') {

				if (nums_to_match.find(current_num) != nums_to_match.end()) current_matches++;
				
				current_num = 0;
			}
			else {
				current_num *= 10;
				current_num += current_line[idx] - '0';
			}
			idx++;
		}

		if (current_num != 0) {
			current_matches = (nums_to_match.find(current_num) != nums_to_match.end()) ? current_matches + 1 : current_matches;
			current_num = 0;
		}

		for (int i = 1; i <= current_matches; i++) {
			card_counts[id + i] += card_counts[id];
		}
	}

	for (auto& x : card_counts) {
		result += x.second;
	}
	
	return result;
}
