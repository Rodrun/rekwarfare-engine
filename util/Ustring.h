#pragma once

#include <vector>
#include <string>

namespace rekwarfare {
    std::vector<std::string> parse(std::string src, std::string delim);
    // Replace occurences of 'search' with 'replace' in 'src'
    void replaceAll(std::string& src, const std::string search,
        const std::string replacestr);
    std::string toUpperCase(std::string);
    std::string toLowerCase(std::string);
}
