#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>

bool compare_by_value_1(const std::string& hand_1, const std::string& hand_2) {
	
	static std::unordered_map<char, int> values = { {'A', 14},{'K', 13},{'Q', 12},{'J', 11},{'T', 10},{'9', 9},{'8', 8},{'7', 7},{'6', 6},{'5', 5},{'4',4},{'3',3},{'2',2} };

	for (int i = 0; i < 5; i++) {

		if (values[hand_1[i]] == values[hand_2[i]]) {
			continue;
		}

		return (values[hand_1[i]] > values[hand_2[i]]);
	}

	return false;
}

bool is_greater_1(const std::string& hand_1, const std::string& hand_2) {

	std::unordered_map<char, int> hand_1_counts;
	std::unordered_map<char, int> hand_2_counts;

	int pairs_1 = 0, pairs_2 = 0;
	int tripples_1 = 0, tripples_2 = 0;
	int highest_count_1 = 0, highest_count_2 = 0;
	bool full_house_flag_1 = false, full_house_flag_2 = false;
	
	for (int i = 0; i < 5; i++) {

		hand_1_counts[hand_1[i]]++;
		hand_2_counts[hand_2[i]]++;
		highest_count_1 = (highest_count_1 > hand_1_counts[hand_1[i]]) ? highest_count_1 : hand_1_counts[hand_1[i]];
		highest_count_2 = (highest_count_2 > hand_2_counts[hand_2[i]]) ? highest_count_2 : hand_2_counts[hand_2[i]];

		if (hand_1_counts[hand_1[i]] == 2) {
			pairs_1++;
		}
		else if (hand_1_counts[hand_1[i]] == 3) {
			pairs_1--;
			tripples_1++;
		}
		else if (hand_1_counts[hand_1[i]] == 4) {
			tripples_1--;
		}

		if (hand_2_counts[hand_2[i]] == 2) {
			pairs_2++;
		}
		else if (hand_2_counts[hand_2[i]] == 3) {
			pairs_2--;
			tripples_2++;
		}
		else if (hand_2_counts[hand_2[i]] == 4) {
			tripples_2--;
		}
	}

	if (highest_count_1 != highest_count_2) {
		return highest_count_1 > highest_count_2;
	}

	if (highest_count_1 > 3) {
		return compare_by_value_1(hand_1, hand_2);
	}

	full_house_flag_1 = (tripples_1 == 1 && pairs_1 == 1);
	full_house_flag_2 = (tripples_2 == 1 && pairs_2 == 1);

	if (full_house_flag_1 != full_house_flag_2) return full_house_flag_1;
	
	if (full_house_flag_1) return compare_by_value_1(hand_1, hand_2);
	
	if (tripples_1 != tripples_2) return (tripples_1 > tripples_2);
	
	if (tripples_1 > 0 && tripples_1 == tripples_2) return compare_by_value_1(hand_1, hand_2);
	
	if (pairs_1 != pairs_2) return pairs_1 > pairs_2;
	
	return compare_by_value_1(hand_1, hand_2);
}

int Find_Winnings_1(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<std::string> hands;
	int result = 0;

	while (std::getline(file, current_line)) {
		hands.push_back(current_line);
	}

	std::sort(hands.rbegin(), hands.rend(), is_greater_1);

	for (int i = 0; i < hands.size(); i++) {
		result += (i + 1) * std::stoi(hands[i].substr(6));
	}

	return result;
}
