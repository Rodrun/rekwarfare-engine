#include "UFile.h"

#include "Ustring.h"

#include <fstream>
#include <string>

namespace rekwarfare {

std::string getFileData(std::ifstream& f) {
    auto buf = new char[getFileSize(f)];
    f.read(buf, getFileSize(f));
    f.close();
    std::string r = buf;
    r += "\0";
    delete[] buf;
    return r;
}

int getFileSize(std::ifstream& f) {
    f.seekg(0, f.end);
    int l = f.tellg();
    f.seekg(0, f.beg);
    return l;
}

std::string getFileName(std::string path) {
    auto p = parse(path, "/");
    if (p.size() == 0) {
        return "";
    }
    return p[p.size() - 1];
}

std::string getFileName_ne(std::string path) {
    return parse(getFileName(path), ".")[0];
}

}
