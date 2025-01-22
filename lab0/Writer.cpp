

#include "Writer.h"
#include <fstream>
#include <string>
#include <list>

#define PERCENT 100

void Writer::Write(const std::list<std::pair<std::string, unsigned>>& list_map, double number_of_words) {
    if (write_file_.is_open()) {
        for (const auto& pair : list_map) {
            write_file_ << pair.first << ";" << pair.second << ";" << (static_cast<double>(pair.second) / number_of_words) * PERCENT << std::endl;
        }
    }
}
