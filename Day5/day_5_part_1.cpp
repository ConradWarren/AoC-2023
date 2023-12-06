#include <fstream>
#include <iostream>

long long Find_Smallest_Location(const std::string& input_file_path) {

std::ifstream file(input_file_path);
std::string current_line;
std::vector<long long> seeds;
std::vector<bool> mapped_seeds;
long long result = INT_MAX;
long long current_num = 0;
long long first_num = 0;
long long second_num = 0;
long long range = 0;
long long diff = 0;

std::getline(file, current_line);

for (int i = 7; i < current_line.length(); i++) {

    if (current_line[i] != ' ') {
        current_num *= 10;
        current_num += current_line[i] - '0';
    }
    else if(current_num != 0){
        seeds.push_back(current_num);
        current_num = 0;
    }
}

if (current_num != 0) {
    seeds.push_back(current_num);
    current_num = 0;
}

mapped_seeds.resize(seeds.size(), false);

while (std::getline(file, current_line)){

    if (current_line.empty()) {
        std::getline(file, current_line);
        std::fill(mapped_seeds.begin(), mapped_seeds.end(), false);
        continue;
    }

    second_num = -1;
    first_num = -1;
    range = -1;

    for (int i = 0; i < current_line.length(); i++) {

        if (current_line[i] != ' ') {
            current_num *= 10;
            current_num += current_line[i] - '0';
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

        if (mapped_seeds[i]) continue;

        if (second_num <= seeds[i] && second_num + range > seeds[i]) {
            seeds[i] += diff;
            mapped_seeds[i] = true;
        }
    }

}

for (int i = 0; i < seeds.size(); i++) {
    result = (result < seeds[i]) ? result : seeds[i];
}

return result;
}
