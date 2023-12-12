#include <fstream>
#include <string>
#include <vector>

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

void Expand(std::string& line, std::vector<int>& nums) {

std::string new_line;
std::vector<int> new_nums(nums.size() * 5);

for (int i = 0; i < nums.size() * 5; i++) {
    new_nums[i] = nums[i % nums.size()];
}
for (int i = 0; i < 4; i++) {
    new_line += line + "?";
}
line = new_line + line;
nums = new_nums;
}

long long Count_Valid(std::string& line, std::vector<int>& nums, int idx, int idx_nums, int current_streak, std::vector<std::vector<std::vector<long long>>>& cache) {

if (idx >= line.length() && (idx_nums >= nums.size() || (idx_nums + 1 == nums.size() && nums[idx_nums] == current_streak))) {
    return 1;
}
if (idx >= line.length()) {
    return 0;
}

if (cache[idx][idx_nums][current_streak] != -1) {
    return cache[idx][idx_nums][current_streak];
}

if (idx_nums >= nums.size()) {
    return cache[idx][idx_nums][current_streak] = (line[idx] == '#') ? 0 : Count_Valid(line, nums, idx + 1, idx_nums, current_streak, cache);
}

if (line[idx] == '.' && current_streak == 0) {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums, current_streak, cache);
}
else if (line[idx] == '.' && current_streak == nums[idx_nums]) {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums + 1, 0, cache);
}
else if (line[idx] == '.') {
    return cache[idx][idx_nums][current_streak] = 0;
}

if (line[idx] == '#' && current_streak == nums[idx_nums]) {
    return cache[idx][idx_nums][current_streak] = 0;
}
else if (line[idx] == '#') {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1, cache);
}

if (line[idx] == '?' && current_streak == 0) {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1, cache) + Count_Valid(line, nums, idx + 1, idx_nums, current_streak, cache);
}
else if (line[idx] == '?' && current_streak == nums[idx_nums]) {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums + 1, 0, cache);
}
else if (line[idx] == '?') {
    return cache[idx][idx_nums][current_streak] = Count_Valid(line, nums, idx + 1, idx_nums, current_streak + 1, cache);
}
}

long long Find_Sum_of_Valid_Combos(const std::string& input_file_path) {

std::ifstream file(input_file_path);
std::string current_line;
long long result = 0;
std::vector<int> nums;
std::string line;
int idx = 0;


while (std::getline(file, current_line)){
    std::vector<std::vector<std::vector<long long>>> cache;
    idx = 0;
    while (idx < current_line.length() && current_line[idx] != ' '){
        idx++;
    }
    nums = Split_Nums(current_line.substr(idx));
    line = current_line.substr(0, idx);
    Expand(line, nums);
    cache.resize(line.length(), std::vector<std::vector<long long>>(nums.size() + 1, std::vector<long long>(20, -1)));
    result += Count_Valid(line, nums, 0, 0, 0, cache);
}

return result;
}
