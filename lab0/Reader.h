//
// Created by PC on 13.10.2024.
//

#ifndef LAB0_READER_H
#define LAB0_READER_H
#include "string"
#include "fstream"
#include "list"
#include "string"
using std::string;
using std::pair;
using std::list;


class Reader {
    string file_name_;
    std::ifstream show_file_;

public:
    Reader(string file_name) : file_name_(file_name)   {
        show_file_.open(file_name_);

    }
    ~Reader() {
        if (show_file_.is_open()){
            show_file_.close();
        }
    }
   bool ReadLine(string& line);
};


#endif //LAB0_READER_H
