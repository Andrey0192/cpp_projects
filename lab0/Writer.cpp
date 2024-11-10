//
// Created by PC on 13.10.2024.
//

#include "Writer.h"
#include "fstream"
#include "string"
#include "list"
#include "string"
using std::string;
using std::pair;
using std::list;
#define KPERCENT 100


void Writer::Write(std::list<std::pair<std::string, unsigned int>> list_map, double number_of_words) {
    if (write_file_.is_open()) {
        for (auto& pair:list_map) {
            write_file_ << pair.first << ";" << pair.second << ";" << (pair.second / number_of_words) * KPERCENT << std::endl;
        }
    }
}