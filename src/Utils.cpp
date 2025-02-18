#include "Utils.h"

#include <string>
#include <vector>

std::pair<std::string, std::string> parse_command(std::string &s)
{
    size_t nonspace_front = 0;
    while (nonspace_front < s.size() && s[nonspace_front] == ' ')
        nonspace_front++;

    if (nonspace_front == s.size())
        return {"", ""};

    size_t space_after_command = nonspace_front + 1;
    while (space_after_command < s.size() && s[space_after_command] != ' ')
        space_after_command++;

    if (space_after_command == s.size())
        return {s.substr(nonspace_front), ""};

    size_t nonspace_back = s.size() - 1;
    while (nonspace_back > space_after_command && s[nonspace_back] == ' ')
        nonspace_back--;

    if (nonspace_back == space_after_command)
        return {s.substr(nonspace_front), ""};

    size_t nonspace_after_command = space_after_command + 1;
    while (s[nonspace_after_command] == ' ')
        nonspace_after_command++;

    return {s.substr(nonspace_front, space_after_command - nonspace_front),
            s.substr(nonspace_after_command, nonspace_back - nonspace_after_command + 1)};
}