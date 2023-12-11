#include <fstream>
#include <unordered_set>
#include <vector>
#include <string>

long long Find_Distance_Sum(const std::string& input_file_path) {

	std::ifstream file(input_file_path);
	std::string current_line;
	std::unordered_set<int> valid_rows;
	std::unordered_set<int> valid_columns;
	std::vector<std::pair<int, int>> valid_points;
	int rows = 0;
	long long result = 0;
	int y = 0, x = 0, direction = 0;

	while (std::getline(file, current_line)){
		for (int i = 0; i < current_line.size(); i++) {
			if (current_line[i] == '#') {
				valid_rows.insert(rows);
				valid_columns.insert(i);
				valid_points.push_back({ rows, i });
			}
		}
		rows++;
	}

	for (int i = 0; i < valid_points.size(); i++) {

		for (int j = i + 1; j < valid_points.size(); j++) {

			y = valid_points[i].first;
			x = valid_points[i].second;
			direction = (y < valid_points[j].first) ? 1 : -1;

			while (y != valid_points[j].first) {
				y += direction;
				if (valid_rows.find(y) == valid_rows.end()) {
					result += 99999;
				}
				result++;
			}

			direction = (x < valid_points[j].second) ? 1 : -1;

			while (x != valid_points[j].second) {
				x += direction;
				if (valid_columns.find(x) == valid_columns.end()) {
					result += 99999;
				}
				result++;
			}
		}

	}

	return result;
}
