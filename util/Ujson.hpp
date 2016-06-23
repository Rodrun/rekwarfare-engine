#pragma once

#include "lib/json11/json11.hpp"

#include <string>

namespace rekwarfare {
    // Returns error string given by json11::Json::parse()
    std::string parseJsonFile(std::string path, json11::Json& j);
}
