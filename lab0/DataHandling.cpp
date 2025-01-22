//
// Created by PC on 13.10.2024.
//
#include "DataHandling.h"
#include <list>
#include <string>
using std::string;
using std::pair;
using std::list;

bool DataHandling::IsDelimer(char& symbol){
    return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void DataHandling::AddMap(std::string &Line) {
    string word = "";
    unsigned size = Line.size();
    if (size == 0 ){ return;}
    for (int i = 0; i <= size - 1; ++i) {
        char symbol = Line[i];
        if ( !IsDelimer(symbol) && i != Line.size()-1) {word += symbol;continue;}
        if ( !IsDelimer(symbol) && i == Line.size()-1) {
            word += symbol;
            if(word.empty()) { continue;}
            words_count_++;
            if (mymap_.find(word) != mymap_.end()) {
                mymap_[word]++;
                word.clear();
                continue;
            }
            mymap_[word] = 1;
            word.clear();
            continue;
        }
        if (IsDelimer(symbol) || i == Line.size()-1){
            if(word.empty()) { continue;}
            words_count_++;
            if (mymap_.find(word) != mymap_.end()) {
                mymap_[word]++;
                word.clear();
                continue;
            }
            mymap_[word] = 1;
            word.clear();
        }
    }
}

bool filter (const std::pair<std::string ,unsigned > & first_element,const std::pair<std::string ,unsigned >& second_element){
    if( first_element.second>second_element.second){
        return true;
    } else{
        return false;
    }
};

void DataHandling::SortListMap(){
    list_map_.assign(mymap_.cbegin(), mymap_.cend());
    list_map_.sort(filter);

}

list<pair<string, unsigned>>DataHandling::ReturnListMap () {
    return list_map_;
}
unsigned DataHandling::GetWordsCount() const {
    return words_count_;
}
