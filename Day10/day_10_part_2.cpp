#include <fstream>
#include <map>
#include <string>
#include <vector>

enum directions{none = 0,up = 1,down = 2,left = 4,right = 8};

std::map<char, int> direction_map = { { '|', up | down },
{ '-', left | right },
{ 'L', up | right },
{ 'J', up | left },
{ '7', down | left },
{ 'F', down | right },
{ '.', none },
{ 'S', up | down | left | right } };

int Find_Area(const std::string& file_input_path) {

std::vector<std::string> graph;
std::ifstream file(file_input_path);
std::string current_line;
int start_y = -1, start_x = -1;
int y = 0, x = 0;
int area = 0; int distance = 0;

while (std::getline(file, current_line)) {

    for (int i = 0; i < current_line.length() && start_y == -1; i++) {
        if (current_line[i] == 'S') {
            start_y = graph.size();
            start_x = i;
        }
    }
    graph.push_back(current_line);
}

y = start_y;
x = start_x;

int rows = graph[0].size() - 1, columns = graph.size() - 1;

while (true) {
    char& c = graph[x][y];
    if (y < rows && direction_map[c] & right && direction_map[graph[x][y + 1]] & left) {
        area += x;
        y++;
    }
    else if (x < columns && direction_map[c] & down && direction_map[graph[x + 1][y]] & up) {
        area -= y;
        x++;
    }   
    else if (y > 0 && direction_map[c] & left && direction_map[graph[x][y - 1]] & right) {
        area -= x;
        y--;
    }   
    else if (x > 0 && direction_map[c] & up && direction_map[graph[x - 1][y]] & down) {
        area += y;
        x--;
    }
    else {
        break;
    }
    c = '.';
    distance++;
}
area += x * start_y - y * start_x;

return (std::abs(area) - distance) / 2 + 1;
}
