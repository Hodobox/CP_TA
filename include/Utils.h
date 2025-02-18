#include <string>
#include <utility>
#include <vector>

// parses the command `s` into the command and the argument
std::pair<std::string, std::string> parse_command(std::string &s);