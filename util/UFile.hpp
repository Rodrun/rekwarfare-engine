#pragma once

#include <fstream>
#include <string>

namespace rekwarfare {
    std::string getFileData(std::ifstream& f);
    int getFileSize(std::ifstream& f);
    // PROBABLY won't work on windoze in some cases
    std::string getFileName(std::string path);
    // Gets file name WITHOUT the extension
    std::string getFileName_ne(std::string path);
}
