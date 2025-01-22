
#include "DataHandling.h"
#include <cctype>
#include <algorithm>

bool DataHandling::Delimiter(char& symbol) {
    return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void DataHandling::AddMap(std::string& line) {
    std::string word;
    for (size_t i = 0; i < line.size(); ++i) {
        char symbol = line[i];
        if (!Delimiter(symbol)) {
            word += symbol;
        }
        if (Delimiter(symbol) || i == line.size() - 1) {
            if (!word.empty()) {
                ++words_count_;
                ++word_count_map_[word];
                word.clear();
            }
        }
    }
}

void DataHandling::SortListMap() {
    sorted_word_list_.assign(word_count_map_.cbegin(), word_count_map_.cend());
    sorted_word_list_.sort([](const auto& first, const auto& second) {
        return first.second > second.second;
    });
}

std::list<std::pair<std::string, unsigned>> DataHandling::ReturnListMap() const {
    return sorted_word_list_;
}

unsigned DataHandling::GetWordsCount() const {
    return words_count_;
}
