#include "UJson.hpp"

#include "UFile.hpp"

#include "lib/json11/json11.hpp"

#include <string>
#include <fstream>

namespace rekwarfare {

std::string parseJsonFile(std::string path, json11::Json& j) {
    std::ifstream fs(path);
    if (!fs) {
        return "(Ujson) Could not open " + path;
    }

    std::string contents = getFileData(fs);
    fs.close();

    std::string err;
    j = json11::Json::parse(contents, err);
    return err;
}

}
