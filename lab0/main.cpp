#include <iostream>
#include "Writer.h"
#include "Reader.h"
#include "DataHandling.h"


//char *argv[]
int main() {

//    std::string file_input  = argv[1];
//    std::string file_output  = argv[2];
//    std::string line;
//
//    if ( count <3) {
//        std::cerr << "not enough arguments" << std::endl;
//        return 1;
//    }
    std::string fileInput  = "input.txt";
    std::string fileOutput  = "output.csv";
    std::string line;

    Reader reader (fileInput);
    DataHandling data ;
    while (reader.ReadLine(line)){
//        if(!reader.ReadLine(Line)){
//            std::cout << "error read data from file" << std::endl;
//            break;
//        }
        data.AddMap(line);
    }
    data.SortListMap();
    Writer writer(fileOutput);
    writer.Write(data.ReturnListMap(), data.GetWordsCount());
    return 0;

}

#include <iostream>
#include "Writer.h"
#include "Reader.h"
#include "DataHandling.h"

int main() {
    std::string fileInput = "input.txt";
    std::string fileOutput = "output.csv";
    std::string line;

    Reader reader(fileInput);
    DataHandling data;
    while (reader.ReadLine(line)) {
        data.AddMap(line);
    }

    data.SortListMap();

    Writer writer(fileOutput);
    writer.Write(data.ReturnListMap(), data.GetWordsCount());

    return 0;
}