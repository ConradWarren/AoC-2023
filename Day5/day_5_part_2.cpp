#include <fstream>
#include <string>

long long Find_Smallest_Location_Range(const std::string& input_file_path) {

std::ifstream file(input_file_path);
std::string current_line;
long long result = INT_MAX;
long long current_num = 0;
long long first_num = -1;
long long second_num = -1;
long long range = 0;
long long diff = 0;
std::vector<std::pair<long long, long long>> seeds;
std::vector<bool> mapped_seeds;

std::getline(file, current_line);

for (int i = 7; i < current_line.length(); i++) {

    if (current_line[i] != ' ') {
        current_num = (current_num * 10) + current_line[i] - '0';
    }
    else if (first_num == -1) {
        first_num = current_num;
        current_num = 0;
    }
    else {
        second_num = current_num;
        current_num = 0;
        seeds.push_back({ first_num, first_num + second_num - 1 });
        first_num = -1;
        second_num = -1;
    }
}

if (current_num != 0) {
    second_num = current_num;
    current_num = 0;
    seeds.push_back({ first_num, first_num + second_num -1 });
}

mapped_seeds.resize(seeds.size(), false);

while (std::getline(file, current_line)) {

    if (current_line.empty()) {
        std::getline(file, current_line);
        mapped_seeds.resize(seeds.size());
        std::fill(mapped_seeds.begin(), mapped_seeds.end(), false);
        continue;
    }

    second_num = 0;
    first_num = -1;
    range = -1;

    for (int i = 0; i < current_line.length(); i++) {

        if (current_line[i] != ' ') {
            current_num = (current_num * 10) + current_line[i] - '0';
        }
        else if (first_num == -1) {
            first_num = current_num;
            current_num = 0;
        }
        else {
            second_num = current_num;
            current_num = 0;
        }
    }

    range = current_num;
    current_num = 0;
    diff = first_num - second_num;

    for (int i = 0; i < seeds.size(); i++) {

        if (mapped_seeds[i]) {
            continue;
        }
        if (second_num <= seeds[i].first && second_num + range > seeds[i].second) {
            seeds[i] = { seeds[i].first + diff, seeds[i].second + diff };
            mapped_seeds[i] = true;
        }
        else if (second_num <= seeds[i].first && second_num + range > seeds[i].first) {
            seeds.push_back({ seeds[i].first + diff, second_num + range - 1 + diff });
            mapped_seeds.push_back(true);
            seeds[i].first = second_num + range;
        }
        else if (second_num > seeds[i].first && second_num <= seeds[i].second && second_num + range > seeds[i].second) {
            seeds.push_back({ second_num + diff, seeds[i].second + diff });
            mapped_seeds.push_back(true);
            seeds[i].second = second_num - 1;
        }
        else if (second_num > seeds[i].first && second_num <= seeds[i].second) {
            seeds.push_back({ second_num + diff, second_num + range - 1 + diff});
            seeds.push_back({ second_num + range, seeds[i].second });
            mapped_seeds.push_back(true);
            mapped_seeds.push_back(false);
            seeds[i].second = second_num - 1;
        }
    }
}

for (int i = 0; i < seeds.size(); i++) {
    result = (result < seeds[i].first) ? result : seeds[i].first;
}

return result;
}
