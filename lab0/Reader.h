
#pragma once
#include <string>
#include <fstream>
class Reader {
    std::string file_name_;
    std::ifstream show_file_;
public:
    explicit Reader(std::string file_name) : file_name_(file_name) {
        show_file_.open(file_name_);
    }

    ~Reader() {
        if (show_file_.is_open()) {
            show_file_.close();
        }
    }

    bool ReadLine(std::string& line);
};
