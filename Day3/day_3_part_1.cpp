#include <vector>
#include <queue>
#include <fstream>

void Breadth_First_Search(std::vector<std::string>& grid, std::queue<std::pair<int, int>>& node_queue, std::vector<std::vector<bool>>& is_valid) {

	std::vector<std::pair<int, int>> directions = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1, 1} };
	int y = 0, x = 0, temp_y = 0, temp_x = 0;

	while (!node_queue.empty()){

		y = node_queue.front().first;
		x = node_queue.front().second;

		is_valid[y][x] = true;
		node_queue.pop();

		
		for (int i = 0; i < directions.size(); i++) {

			temp_y = y + directions[i].first;
			temp_x = x + directions[i].second;

			if (temp_y < 0 || temp_x < 0 || temp_y >= grid.size() || temp_x >= grid[0].size()) {
				continue;
			}

			if (is_valid[temp_y][temp_x]) {
				continue;
			}

			if (grid[temp_y][temp_x] != '.') {
				node_queue.push({ temp_y, temp_x });
				is_valid[temp_y][temp_x] = true;
			}

		}
	}

}

int Find_Part_Number_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<std::string> grid;
	std::vector<std::vector<bool>> is_valid_part;
	std::queue<std::pair<int, int>> node_queue;
	int line_idx = 0;
	int result = 0;
	int current_num = 0;

	while (std::getline(file, current_line)){

		for (int i = 0; i < current_line.length(); i++) {
			if (current_line[i] != '.' && (current_line[i] - '0' < 0 || current_line[i] - '0' > 9)) {
				node_queue.push({ line_idx, i });
			}
		}
		grid.push_back(current_line);
		line_idx++;
	}

	is_valid_part.resize(grid.size(), std::vector<bool>(grid[0].size(), false));

	Breadth_First_Search(grid, node_queue, is_valid_part);
	
	for (int i = 0; i < grid.size(); i++) {
		
		current_num = 0;

		for (int j = 0; j < grid[0].size(); j++) {

			if (!is_valid_part[i][j]) {
				result += current_num;
				current_num = 0;
				continue;
			}

			if (grid[i][j] - '0' >= 0 && grid[i][j] - '0' < 10) {
				current_num *= 10;
				current_num += (grid[i][j] - '0');
			}
			else{
				result += current_num;
				current_num = 0;
			}
		}
		result += current_num;
	}

	return result;
}
