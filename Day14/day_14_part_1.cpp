#include <fstream>
#include <string>
#include <vector>

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
            result += grid.size() - i;
        }
    }

    return result;
}
