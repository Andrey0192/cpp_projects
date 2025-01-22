#include <fstream>
#include <iterator>
#include <utility>
#include <string>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <string>
#include <ios>
#include <fstream>
#include "utils.h"
const char NULL_TERMINATOR = '\0';
inline const char CARRIAGE_RETURN_CHAR = '\r';

enum class State{
    INVALID,
    MOVABLE,
    PRE_END,
    END
};
struct Settings{
    char DELIMETERS;
    char SKIP_CHARACTER;
    char NEW_LINE_CHARACTERS;
};

template<typename ...Types>
class SCVParser;

std::pair<size_t, std::string> take_substring(std::string_view string, Settings settings, size_t offset);

template<typename T>
void extract_token(T& token, const std::string& string, size_t col){

    std::istringstream string_stream(string);
    string_stream >> token;

    if (string_stream.fail() || !string_stream.eof()) {
        throw std::invalid_argument( + "\nCol: " + std::to_string(col+1) + " \n--- " + string);
    }
}

template<size_t index,typename ...Types>
void take_tuple(std::tuple<Types...>& tuple,std::string_view line,Settings settings,size_t offset){

    auto [index_next, string] = take_substring(line, settings, offset);
    extract_token(std::get<index>(tuple), string,index);

    if constexpr (index < sizeof...(Types)-1) {
        take_tuple<index + 1, Types...>(tuple, line, settings, index_next + offset+1);

    }
}

template<typename ...Types>
void parse_tuple(std::tuple<Types...>& tuple,std::string_view line,Settings settings){
    take_tuple<0,Types...>(tuple, line, settings,0);
}

template<typename ...Types>
class Iterator {
public:
    Iterator(): _file_position(0) ,_state(State::INVALID), _parser(nullptr), _tuple{}{};
    //    _iterators_start_lines(0),

    bool operator==(const Iterator& it) const{
        std::cout <<(it._state == this->_state) << "\n";
        std::cout <<it._file_position <<"  "<<this->_file_position << "\n";
        return it._state == this->_state && it._file_position == this->_file_position;

    }
    bool operator!=(const Iterator& it) const{
        return !(it == *this);
    }

    const std::tuple<Types...>& operator*() const{
        if (this->_state == State::INVALID){
            std::cout << " 1 \n"; }
        if (this->_state == State::END){
            std::cout << "2\n";}
        return this->_tuple;
    }

    Iterator& operator+=(size_t offset){
        if (!offset){
            return *this;
        }

        if (this->_state == State::INVALID){
            std::cout << "3\n";        }

        if (this->_state == State::END){
            throw std::invalid_argument("END");
        }

        if (this->_state == State::PRE_END){
            if (offset > 1){
                std::cout << "5\n";            }
            std::cout << "45\n";

            this->_state = State::END;
        }

        if (this->_state == State::MOVABLE){
            read_tuple(offset);
        }

        return *this;
    }

    virtual ~Iterator() = default;


protected:
    SCVParser<Types...>* _parser;
    State _state;
    std::streamoff _file_position;
//    size_t _iterators_start_lines;
    std::tuple<Types...> _tuple{};
    virtual void read_tuple(size_t offset)=0;
};




template<typename ...Types>
class ForwardIterator: public Iterator<Types...>{
public:
    friend SCVParser<Types...>;
    ForwardIterator(): Iterator<Types...>() {}
    ForwardIterator& operator++(){
        *this += 1;
        return *this;
    }
    ForwardIterator operator++(int){
        auto result = *this;
        (*this) += 1;
        return result;
    }
    void read_tuple(size_t offset) override {
        this->_parser->_ifstream.clear();
        this->_parser->_ifstream.seekg(this->_file_position);
        std::string line;
        for (size_t i = 0; i < offset; ++i) {
            if (!std::getline(this->_parser->_ifstream, line, this->_parser->_setings.NEW_LINE_CHARACTERS)) {
                this->_state = State::END;
                return;
            }
            if (this->_state == State::END && this->_parser->_ifstream.fail()){
                std::cout << "6\n";

            }

            if (this->_parser->_ifstream.fail()){
                this->_state = State::END;

            }
            else if (this->_parser->_ifstream.eof()){
                this->_state = State::PRE_END;


            }
        }

        if (line.back() == CARRIAGE_RETURN_CHAR) {
            line.pop_back(); // Удалить '\r', если он есть
        }
        parse_tuple<Types...>(this->_tuple, line, this->_parser->_setings);

        if (is_next_line_empty(this->_parser->_ifstream)){
            this->_state = State::PRE_END;
            this->_file_position = EOF;
        }else{
            this->_file_position = this->_parser->_ifstream.tellg();
            std::cout <<this->_file_position << "\n";

//            this->_iterators_start_lines += offset;
        }
    }


private:
    explicit ForwardIterator(std::streamoff _start_forward,size_t iterators_strat_lines,State state,SCVParser<Types...>*parser){
        this->_parser =parser;
        this->_file_position=_start_forward;
//        this->_iterators_start_lines=iterators_strat_lines;
        this->_state=state;
        this->_tuple={};
        if (state != State::END){
            read_tuple(1);
        }
    }

};




template<typename ...Types>
ForwardIterator<Types...> operator+(const ForwardIterator<Types...>& it, size_t delta){
    auto result = it;
    result += delta;
    return result;
}

template<typename ...Types>
ForwardIterator<Types...> operator+(size_t delta, const ForwardIterator<Types...>& it){
    return it + delta;
}



template<typename ...Types>
class SCVParser {

public:
    friend ForwardIterator<Types...>;

    SCVParser(const char* path, const Settings& settings,
              size_t skip_first_lines_count){

        _ifstream = std::ifstream (path,std::fstream::binary);//иначе некоторые функции не работают
        if (!_ifstream.is_open()){std::cerr<<"ошибка открытия";}

        std::string line;
        for (unsigned int i = 0; i < skip_first_lines_count; i++){
            std::getline(_ifstream, line, settings.NEW_LINE_CHARACTERS);
        }
        _start_forward= _ifstream.tellg();
        if(_ifstream.fail()){std::cerr<<"ошибка чтения строк";}

        _ifstream.clear();
        _iterators_skip_lines=skip_first_lines_count;
        _setings =settings;

    }
    ForwardIterator<Types...> begin(){
        return ForwardIterator<Types...>(_start_forward, _iterators_skip_lines, State::MOVABLE, this);
    }
    ForwardIterator<Types...> end(){
        return ForwardIterator<Types...>(EOF, 0, State::END, this);
    }
private:

    std::ifstream _ifstream;
    std::streamoff _start_forward;
    size_t _iterators_skip_lines;
    Settings _setings;


};



