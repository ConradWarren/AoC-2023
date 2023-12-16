#include <set>
#include <vector>
#include <string>
#inlcude <queue>
#include <fstream>

int Breadth_First_Search(std::vector<std::string>& grid) {

	std::queue<std::vector<int>> node_queue;
	std::vector<std::vector<std::set<std::pair<int, int>>>> cache(grid.size(), std::vector<std::set<std::pair<int, int>>>(grid[0].size()));

	int count = 0;

	node_queue.push({ 0,-1,0,1 });

	while (!node_queue.empty()){

		int y = node_queue.front()[0] + node_queue.front()[2];
		int x = node_queue.front()[1] + node_queue.front()[3];
		int y_direction = node_queue.front()[2];
		int x_direction = node_queue.front()[3];
		node_queue.pop();

		if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size() || cache[y][x].find({ y_direction, x_direction }) != cache[y][x].end()) {
			continue;
		}

		if (cache[y][x].empty()) count++;

		cache[y][x].insert({ y_direction, x_direction });
		
		if (grid[y][x] == '.' || (y_direction == 0 && grid[y][x] == '-') || (x_direction == 0 && grid[y][x] == '|')) {
			node_queue.push({ y, x, y_direction, x_direction });
		} 
		else if (grid[y][x] == '/') node_queue.push({ y, x, -x_direction, -y_direction });
		
		else if (grid[y][x] == '\\') node_queue.push({ y, x, x_direction, y_direction });
		
		else if (grid[y][x] == '-') {
			node_queue.push({ y, x, 0, 1 });
			node_queue.push({ y, x, 0, -1 });
		}
		else if (grid[y][x] == '|') {
			node_queue.push({ y,x, 1, 0 });
			node_queue.push({ y,x, -1, 0 });
		}
	}
	return count;
}

int Count_Energized_Cells(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::vector<std::string> grid;
	std::string line;
	int result = 0;
	int current = 0;

	while (std::getline(file, line)){
		grid.push_back(line);
	}

	return Breadth_First_Search(grid);
}
