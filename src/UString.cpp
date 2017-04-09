#include "UString.hpp"

#ifdef _WIN32
#	include <cctype>
#endif
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

namespace rekwarfare {
std::vector<std::string> parse(std::string src, std::string delim) {
    std::vector<std::string> rbuf;

    char* sc = new char[src.size() + 1];
    strcpy(sc, src.c_str());
    char* token = strtok(sc, delim.c_str());

    while (token != 0) {
        std::string b(token);
        rbuf.push_back(b);
        token = strtok(NULL, delim.c_str());
    }
    delete[] sc;
    delete token;
    return rbuf;
}

void replaceAll(std::string& src, std::string search, std::string replacestr) {
    auto pos = 0;
    while ((pos = src.find(search, pos)) != std::string::npos) {
        src.replace(pos, search.length(), replacestr);
        pos += replacestr.length();
    }
}

std::string toUpperCase(std::string src) {
    auto ret = src;
    std::transform(ret.begin(), ret.end(), ret.begin(),
        (int (*)(int)) std::toupper);
    return ret;
}

std::string toLowerCase(std::string src) {
    auto ret = src;
    std::transform(ret.begin(), ret.end(), ret.begin(),
        (int (*)(int)) std::tolower);
    return ret;
}

}
