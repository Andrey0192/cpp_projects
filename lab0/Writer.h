//
// Created by PC on 13.10.2024.
//

#ifndef LAB0_WRITER_H
#define LAB0_WRITER_H
#include "list"
#include "fstream"
#include "string"
#include "list"
#include "string"
using std::string;
using std::pair;
using std::list;

class Writer {
    std::string file_name_;
    std::ofstream write_file_;
public:
    Writer(std::string file_name) : file_name_(file_name)   {
        write_file_.open(file_name_);

    }
    ~Writer() {
        if (write_file_.is_open()){
            write_file_.close();
        }
    }
    void Write(std::list<std::pair<std::string, unsigned>> list_map,  double number_of_words  );
};

#endif //LAB0_WRITER_H
