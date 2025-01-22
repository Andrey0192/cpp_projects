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
