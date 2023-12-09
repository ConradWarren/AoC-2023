#include <fstream>
#include <vector>
#include <algorithm>

void Split_Nums(const std::string& source_nums, std::vector<long long>& dest_nums) {

	long long current_num = 0;
	bool negative_flag = false;
	bool found_num_flag = false;
	for (int i = 0; i < source_nums.length(); i++) {
		
		if (source_nums[i] == '-') {
			negative_flag = true;
			found_num_flag = true;
		}
		else if (source_nums[i] != ' ') {
			current_num = (current_num * 10) + (source_nums[i] - '0');
			found_num_flag = true;
		}
		else if (found_num_flag) {
			dest_nums.push_back((negative_flag) ? -current_num : current_num);
			negative_flag = false;
			found_num_flag = false;
			current_num = 0;
		}
	}

	if (found_num_flag) {
		dest_nums.push_back((negative_flag) ? -current_num : current_num);
	}
	
}

long long Pascals_Trianlge(std::vector<long long>& nums) {

	bool all_zero_flag = true;
	std::vector<long long> next_nums(nums.size() - 1);
	
	for (int i = 0; i < nums.size() - 1; i++) {
		next_nums[i] = nums[i + 1] - nums[i];
		all_zero_flag = (next_nums[i] != 0) ? false : all_zero_flag;
	}

	return all_zero_flag ? nums.back() : nums.back() + Pascals_Trianlge(next_nums);
}

long long Find_Next_Number(const std::string& file_input_path) {

	std::ifstream file(file_input_path);
	std::string current_line;
	std::vector<long long> nums;
	bool all_zero_flag = false;
	long long result = 0;
	long long temp = 0;

	while (std::getline(file, current_line)){
		Split_Nums(current_line, nums);
		result += Pascals_Trianlge(nums);
		nums.clear();
	}

	return result;
}
