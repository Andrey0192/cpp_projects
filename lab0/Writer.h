
#pragma once
#include <string>
#include <list>
#include <utility>

class Writer {
    std::string file_name_;
    std::ofstream write_file_;
public:
    explicit Writer(std::string file_name) : file_name_(std::move(file_name)) {
        write_file_.open(file_name_);
    }

    ~Writer() {
        if (write_file_.is_open()) {
            write_file_.close();
        }
    }

    void Write(const std::list<std::pair<std::string, unsigned>>& list_map, double number_of_words);
};
