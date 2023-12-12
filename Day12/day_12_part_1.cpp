#include <fstream>
#include <vector>
#include <string>

std::vector<int> Split_Nums(const std::string& source_nums) {

std::vector<int> result;
std::string current_num;

for (int i = 0; i < source_nums.size(); i++) {

    if (source_nums[i] != ',') {
        current_num += source_nums[i];
    }
    else if (!current_num.empty()) {
        result.push_back(std::stoi(current_num));
        current_num.clear();
    }
}

if (!current_num.empty()) {
    result.push_back(std::stoi(current_num));
}

return result;
}

int Count_Valid(std::string& line, std::vector<int>& nums, int idx, int idx_nums, int current_streak) {

  if (idx >= line.length() && (idx_nums >= nums.size() || (idx_nums + 1 == nums.size() && nums[idx_nums] == current_streak))) {
      return 1;
  }
  if (idx >= line.length()) {
      return 0;
  }
  
  if (idx_nums >= nums.size()) {
      return (line[idx] == '#') ? 0 : Count_Valid(line, nums, idx + 1, idx_nums, current_streak);
  }
  
  if (line[idx] == '.' && current_streak == 0) {
      return Count_Valid(line, nums, idx + 1, idx_nums, current_streak);
  }
  else if (line[idx] == '.' && current_streak == nums[idx_nums]) {
      return Count_Valid(line, nums, idx + 1, idx_nums + 1, 0);
  }
  else if (line[idx] == '.') {
      return 0;
  }
  
  if (line[idx] == '#' && current_streak == nums[idx_nums]) {
      return 0;
  }
  else if (line[idx] == '#') {
      return Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1);
  }
  
  if (line[idx] == '?' && current_streak == 0) {
      return Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1) + Count_Valid(line, nums, idx + 1, idx_nums, current_streak);
  }
  else if (line[idx] == '?' && current_streak == nums[idx_nums]) {
      return Count_Valid(line, nums, idx + 1, idx_nums + 1, 0);
  }
  else if (line[idx] == '?') {
      return Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1);
  }
}

int Find_Sum_of_Valid_Combos(const std::string& input_file_path) {

std::ifstream file(input_file_path);
std::string current_line;
int result = 0;
std::vector<int> nums;
std::string line;
int idx = 0;

while (std::getline(file, current_line)){
    idx = 0;
    while (idx < current_line.length() && current_line[idx] != ' '){
        idx++;
    }
    nums = Split_Nums(current_line.substr(idx));
    line = current_line.substr(0, idx);
    result += Count_Valid(line, nums, 0, 0, 0);
}

return result;
}
