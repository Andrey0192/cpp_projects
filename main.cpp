#include <iostream>
//#include "scv_parsing.h"
#include "print_tuple.h"
int main() {
    const char* file_path = "../tmp.csv";
    char delimiter = ',';
    char escape_character = '\\';
    char newline_character = '\n';
    size_t skip_first_lines_count = 0;

    Settings settings{delimiter, escape_character, newline_character};

    SCVParser<std::string, int,float> parser(file_path, settings, skip_first_lines_count);

    for (auto it = parser.begin(); it != parser.end(); it+=1){

        std::cout << "Tuple: " << *it << '\n';
    }

    return 0;
}
