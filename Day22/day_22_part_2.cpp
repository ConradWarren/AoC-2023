#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <fsteam>

std::vector<std::pair<int, int>> Split(const std::string& input) {

	std::string current;
	std::vector<std::pair<int, int>> result(3, {-1, -1});
	int idx = 0;

	for (int i = 0; i < input.length(); i++) {

		if (input[i] != ',' && input[i] != '~') {
			current += input[i];
		}
		else if(result[idx%3].first == -1) {
			result[idx % 3].first = std::stoi(current);
			current.clear();
			idx++;
		}
		else {
			result[idx % 3].second = std::stoi(current);
			current.clear();
			idx++;
		}
	}

	if (!current.empty()) {
		result[idx % 3].second = std::stoi(current);
	}

	return result;
}

bool Sort_Blocks(const std::vector<std::pair<int, int>>& vec_1, const std::vector<std::pair<int, int>>& vec_2) {
	return vec_1[2].first < vec_2[2].first;
}


int Count_Blocks_to_Fall(std::vector<std::unordered_set<int>>& supporting_cache, std::vector<std::unordered_set<int>>& being_supported, int block_idx) {

	std::vector<bool> fallen_cache(supporting_cache.size(), false);
	std::queue<int> node_queue;
	int result = 0;
	int node = 0;

	fallen_cache[block_idx] = true;

	for (int x : supporting_cache[block_idx]) {
		node_queue.push(x);
	}

	while (!node_queue.empty()){

		node = node_queue.front();
		node_queue.pop();

		if (fallen_cache[node]) continue;
		
		bool is_supported = false;
		for (int x : being_supported[node]) {
			if (!fallen_cache[x]) {
				is_supported = true;
				break;
			}
		}

		if (is_supported) continue;
		
		result++;
		fallen_cache[node] = true;

		for (int x : supporting_cache[node]) {
			node_queue.push(x);
		}
	}

	return result;
}

int Find_Falling_Block_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string line;
	std::vector<std::vector<std::pair<int, int>>> blocks;
	std::vector<std::unordered_set<int>> supporting_cache;
	std::vector<std::unordered_set<int>> being_supported_cache;
	int result = 0;

	while (std::getline(file, line)){
		blocks.push_back(Split(line));
	}
	supporting_cache.resize(blocks.size());
	being_supported_cache.resize(blocks.size());
	std::sort(blocks.begin(), blocks.end(), Sort_Blocks);

	for (int i = 0; i < blocks.size(); i++) {

		
		int max_height_hit = 0;

		for (int j = i - 1; j >= 0; j--) {

			bool hit_block = (blocks[i][0].first <= blocks[j][0].second && blocks[i][0].second >= blocks[j][0].first && blocks[i][1].first <= blocks[j][1].second && blocks[i][1].second >= blocks[j][1].first);
			
			if (hit_block && blocks[j][2].second > max_height_hit) {
				being_supported_cache[i].clear();
				being_supported_cache[i].insert(j);
				max_height_hit = blocks[j][2].second;
			}
			else if (hit_block && blocks[j][2].second == max_height_hit) {
				being_supported_cache[i].insert(j);
			}
		}

		blocks[i][2].second += max_height_hit + 1 - blocks[i][2].first;
		blocks[i][2].first = max_height_hit + 1;
	}

	for (int i = 0; i < blocks.size(); i++) {
		for (auto x : being_supported_cache[i]) {
			supporting_cache[x].insert(i);
		}
	}
	
	
	for (int i = 0; i < blocks.size(); i++) {
		result += Count_Blocks_to_Fall(supporting_cache, being_supported_cache, i);
	}
	return result;
}
