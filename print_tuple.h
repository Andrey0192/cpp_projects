#include <iostream>
using std::basic_ostream;
#include <tuple>
#include "scv_parsing.h"


template <size_t index, typename Ch, typename Tr, typename... Args>
void print_tuple(std::basic_ostream<Ch, Tr>& ostream, const std::tuple<Args...>& tuple) {
    if constexpr (index < sizeof...(Args)) {
        ostream << std::get<index>(tuple);
        if constexpr (index + 1 < sizeof...(Args)) {
            ostream << ' ';
        }
        print_tuple<index + 1, Ch, Tr, Args...>(ostream, tuple);
    }
}


template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& ostream, const std::tuple<Args...>& tuple) {
    print_tuple<0, Ch, Tr, Args...>(ostream, tuple);
    return ostream;
}
