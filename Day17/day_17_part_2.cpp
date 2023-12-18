#define In_Range(y, x, y_max, x_max) (y >= 0 && y < y_max && x >=0 && x < x_max)

int Djikstra(const std::vector<std::string>& grid) {

	std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> node_queue;
	std::map<std::vector<int>, int> cache;
	int result = INT_MAX;

	node_queue.push({ 0, 0,0,0,1,0 });
	node_queue.push({ 0, 0,0,1,0,0 });

	while (!node_queue.empty()) {

		int y = node_queue.top()[1];
		int x = node_queue.top()[2];
		int y_dir = node_queue.top()[3];
		int x_dir = node_queue.top()[4];
		int move_count = node_queue.top()[5];
		int heat_loss = node_queue.top()[0];

		node_queue.pop();

		if (y + 1 == grid.size() && x + 1 == grid[0].size()) {
			result = (result < heat_loss) ? result : heat_loss;
			continue;
		}

		int temp_y = y + x_dir;
		int temp_x = x + y_dir;

		if (In_Range(temp_y, temp_x, grid.size(), grid[0].size()) && move_count > 3 && (cache.find({temp_y, temp_x, x_dir, y_dir, 1}) == cache.end() || cache[{temp_y, temp_x, x_dir, y_dir, 1}] > heat_loss + grid[temp_y][temp_x] - '0')) {
			cache[{temp_y, temp_x, x_dir, y_dir, 1}] = heat_loss + grid[temp_y][temp_x] - '0';
			node_queue.push({ heat_loss + grid[temp_y][temp_x] - '0', temp_y, temp_x, x_dir, y_dir, 1 });
		}
		
		temp_y = y - x_dir;
		temp_x = x - y_dir;
		
		if (In_Range(temp_y, temp_x, grid.size(), grid[0].size()) && move_count > 3 && (cache.find({temp_y, temp_x, -x_dir, -y_dir, 1}) == cache.end() || cache[{temp_y, temp_x, -x_dir, -y_dir, 1}] > heat_loss + grid[temp_y][temp_x] - '0')) {
			cache[{temp_y, temp_x, -x_dir, -y_dir, 1}] = heat_loss + grid[temp_y][temp_x] - '0';
			node_queue.push({ heat_loss + grid[temp_y][temp_x] - '0', temp_y, temp_x, -x_dir, -y_dir, 1 });
		}
		
		if (move_count == 10) {
			continue;
		}

		temp_y = y + y_dir;
		temp_x = x + x_dir;
		
		if (In_Range(temp_y, temp_x, grid.size(), grid[0].size()) && (cache.find({temp_y, temp_x, y_dir, x_dir, move_count + 1}) == cache.end() || cache[{temp_y, temp_x, y_dir, x_dir, move_count}] > heat_loss + grid[temp_y][temp_x] - '0')) {
			cache[{temp_y, temp_x, y_dir, x_dir, move_count + 1}] = heat_loss + grid[temp_y][temp_x] - '0';
			node_queue.push({ heat_loss + grid[temp_y][temp_x] - '0', temp_y, temp_x, y_dir, x_dir, move_count + 1 });
		}
		
	}

	return result;
}

int Find_Min_Loss(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::vector<std::string> grid;
	std::map<std::vector<int>, int> cache;
	std::set<std::vector<int>> cycle;

	while (std::getline(file, current_line)){
		grid.push_back(current_line);
	}

	return Djikstra(grid);
}
