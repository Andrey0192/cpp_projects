
#include "Reader.h"
#include <string>

bool Reader::ReadLine(std::string& line) {
    return static_cast<bool>(std::getline(show_file_, line));
}

