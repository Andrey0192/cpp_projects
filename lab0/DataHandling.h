//
// Created by PC on 13.10.2024.
//

#ifndef LAB0_DATAHANDLING_H
#define LAB0_DATAHANDLING_H
#include "list"
#include "string"
#include <map>
using std::string;
using std::pair;
using std::list;



class DataHandling {
    list<pair<string, unsigned>> list_map_;
    std::map<string,unsigned> mymap_;
    unsigned words_count_ = 0;

    static bool IsDelimer(char& symbol);
public:
    void AddMap(string& word);
    unsigned GetWordsCount() const;
    void SortListMap();
    list<pair<string, unsigned>> ReturnListMap ();

};

#endif //LAB0_DATAHANDLING_H
