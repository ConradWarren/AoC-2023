#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

int Cache_Grid(std::vector<std::string>& grid, int count) {

    static std::unordered_map<std::string, int> cache;
    std::string key;

    for (int i = 0; i < grid.size(); i++) {
        key += grid[i];
    }
    if (cache.find(key) != cache.end()) {
        return cache[key];
    }
    cache[key] = count;
    return -1;
}

void Cycle(std::vector<std::string>& grid) {

    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++) {

            if (grid[j][i] != 'O') continue;

            int idx = j - 1;
            while (idx >= 0 && grid[idx][i] == '.') {
                grid[idx][i] = 'O';
                grid[idx + 1][i] = '.';
                idx--;
            }
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {

            if (grid[i][j] != 'O') continue;

            int idx = j - 1;
            while (idx >= 0 && grid[i][idx] == '.') {
                grid[i][idx] = 'O';
                grid[i][idx + 1] = '.';
                idx--;
            }
        }
    }

    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = grid.size()-1; j >= 0; j--) {

            if (grid[j][i] != 'O') continue;

            int idx = j + 1;
            while (idx < grid.size() && grid[idx][i] == '.') {
                grid[idx][i] = 'O';
                grid[idx - 1][i] = '.';
                idx++;
            }
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = grid[0].size() - 1; j >= 0; j--) {

            if (grid[i][j] != 'O') continue;

            int idx = j + 1;
            while (idx < grid[0].size() && grid[i][idx] == '.') {
                grid[i][idx] = 'O';
                grid[i][idx - 1] = '.';
                idx++;
            }
        }
    }

}

int Find_Load_Sum(const std::string& input_file_path) {

    std::ifstream file(input_file_path);
    std::string current_line;
    std::vector<std::string> grid;
    int result = 0;
    int offset = 0;
    int cache_num = 0;

    while (std::getline(file, current_line)){
        grid.push_back(current_line);
    }

    Cache_Grid(grid, 0);
    for (int i = 1; i <= 1000000000; i++) {
        Cycle(grid);
        cache_num = Cache_Grid(grid, i);
        if (cache_num != -1) {
            offset = (1000000000 - i) % (i - cache_num);
            break;
        }
    }

    for (int i = 0; i < offset; i++) {
        Cycle(grid);
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != 'O') continue;
            result += grid.size() - i;
        }
    }

    return result;
}
