
#include "utils.h"
bool is_empty_line(const std::string& string){
    return std::all_of(string.begin(), string.end(), [](const auto& c)
    {
        return std::isspace(c);
    });
}
bool is_next_line_empty(std::ifstream& ifstream){
    auto start_position = ifstream.tellg();

    std::string next_line;

    std::getline(ifstream, next_line);

    ifstream.seekg(start_position);

    return is_empty_line(next_line);
}