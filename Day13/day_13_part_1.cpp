#include <fstream>
#include <vector>
#include <string>

int Find_Axis_of_Reflection(std::vector<std::string>& grid) {

    std::vector<bool> verticle_reflections(grid[0].size()-1, true);
    std::vector<bool> horizontal_reflections(grid.size() - 1, true);
    int idx_1 = 0, idx_2 = 0;

    for (int i = 0; i < grid.size(); i++) {

        for (int j = 0; j < grid[0].size()-1; j++) {

            if (!verticle_reflections[j]) continue;

            idx_1 = j;
            idx_2 = j + 1;

            while (idx_1 >= 0 && idx_2 < grid[0].size()){

                if (grid[i][idx_1] != grid[i][idx_2]) {
                    verticle_reflections[j] = false;
                    break;
                }

                idx_1--;
                idx_2++;
            }
        }
    }

    for (int i = 0; i < verticle_reflections.size(); i++) {
        if (verticle_reflections[i]) return i + 1;
    }

    for (int i = 0; i < grid[0].size(); i++) {

        for (int j = 0; j < grid.size()-1; j++) {

            if (!horizontal_reflections[j]) continue;

            idx_1 = j;
            idx_2 = j + 1;

            while (idx_1 >= 0 && idx_2 < grid.size()){
                if (grid[idx_1][i] != grid[idx_2][i]) {
                    horizontal_reflections[j] = false;
                    break;
                }
                idx_1--;
                idx_2++;
            }
        }
    }

    for (int i = 0; i < horizontal_reflections.size(); i++) {
        if (horizontal_reflections[i]) return 100 * (i + 1);
    }

    return 0;
}

int Find_Reflection_Sum(const std::string& file_input_path) {

    std::ifstream file(file_input_path);
    std::string current_line;
    std::vector<std::string> grid;
    int result = 0;

    while (std::getline(file, current_line)){

        if (current_line.empty()) {
            result += Find_Axis_of_Reflection(grid);
            grid.clear();
        }
        else {
            grid.push_back(current_line);
        }
    }
    result += Find_Axis_of_Reflection(grid);

    return result;
}
