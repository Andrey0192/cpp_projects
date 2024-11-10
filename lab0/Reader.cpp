//
// Created by PC on 13.10.2024.
//

#include "Reader.h"
#include "fstream"
#include "string"
#include "list"
#include "string"
using std::string;
using std::pair;
using std::list;

bool Reader::ReadLine(std::string &line) {
    if (std::getline(show_file_,line) ){
        return true;
    }
    return false;
}


//string Reader::GetFileName() {
//    return file_name_;
//}