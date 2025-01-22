
#pragma once
#include <list>
#include <string>
#include <map>

class DataHandling {
    std::list<std::pair<std::string, unsigned>> sorted_word_list_;
    std::map<std::string, unsigned> word_count_map_;
    unsigned words_count_ = 0;

    bool Delimiter(char& symbol);

public:
    void AddMap(std::string& line);
    unsigned GetWordsCount() const;
    void SortListMap();
    std::list<std::pair<std::string, unsigned>> ReturnListMap() const;
};
