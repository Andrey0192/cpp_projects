
#include <iostream>
#include "scv_parsing.h"


std::pair<size_t, std::string> take_substring(std::string_view string, Settings settings, size_t offset) {
    std::string line;
    char previous_character = NULL_TERMINATOR;
    size_t i;

    for (i = 0; string[i+offset] != NULL_TERMINATOR; ++i) {
        const char c = string[i + offset];
        previous_character = c;
        if (c == settings.DELIMETERS && previous_character == settings.SKIP_CHARACTER) {
            line.append(1, settings.DELIMETERS);
            continue;
        }
        if (c == settings.SKIP_CHARACTER && previous_character == settings.SKIP_CHARACTER) {
            line.append(1, settings.SKIP_CHARACTER);
            continue;
        }
        if (c == settings.DELIMETERS) {
            break;
        }
        if (c == settings.SKIP_CHARACTER) {
            continue;
        }
        line.append(1, c);

    }

    return {i, line};
}
