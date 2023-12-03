#include <vector>
#include <queue>
#include <unordered_set>
#include <fstream>

int Find_Gear_Ratio_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<std::string> grid;
	std::vector<std::vector<int>> part_ids;
	std::queue<std::pair<int, int>> node_queue;
	std::vector<int> id_values;
	std::vector<std::pair<int, int>> directions = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1, 1} };
	std::unordered_set<int> used_ids;
	int y = 0, x = 0, temp_y = 0, temp_x = 0;
	int line_idx = 0;
	int id = 0;
	int current_num = 0;
	int result = 0;

	while (std::getline(file, current_line)) {

		for (int i = 0; i < current_line.length(); i++) {
			if (current_line[i] == '*') {
				node_queue.push({ line_idx, i });
			}
		}
		grid.push_back(current_line);
		line_idx++;
	}

	part_ids.resize(grid.size(), std::vector<int>(grid[0].size(), -1));

	for (int i = 0; i < grid.size(); i++) {

		for (int j = 0; j < grid[0].size(); j++) {

			if ((grid[i][j] - '0' < 0 || grid[i][j] > '9') && current_num == 0) {
				continue;
			}

			if ((grid[i][j] - '0' < 0 || grid[i][j] > '9')) {
				id_values.push_back(current_num);
				current_num = 0;
				id++;
			}
			else {
				part_ids[i][j] = id;
				current_num *= 10;
				current_num += grid[i][j] - '0';
			}
		}

		if (current_num != 0) {
			id_values.push_back(current_num);
			current_num = 0;
			id++;
		}
	}

	while (!node_queue.empty()){

		y = node_queue.front().first;
		x = node_queue.front().second;
		node_queue.pop();

		for (int i = 0; i < directions.size(); i++) {
			
			temp_y = y + directions[i].first;
			temp_x = x + directions[i].second;

			if (temp_y < 0 || temp_x < 0 || temp_y >= grid.size() || temp_x >= grid[0].size()) {
				continue;
			}

			if (part_ids[temp_y][temp_x] == -1) {
				continue;
			}

			used_ids.insert(part_ids[temp_y][temp_x]);
		}

		if (used_ids.size() == 2) {
			current_num = 1;
			for (auto& _id : used_ids) {
				current_num *= id_values[_id];
			}
			result += current_num;
		}
		used_ids.clear();
	}

	return result;
}
