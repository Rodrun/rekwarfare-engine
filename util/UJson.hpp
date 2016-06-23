#pragma once

#include "lib/json11/json11.hpp"

#include <string>

namespace rekwarfare {
/*
* Parse a JSON file and store its contents into a Json object.
* path: Path to the JSON file.
* j: Reference to JSON object.
* returns: error string given by Json::parse().
*/
std::string parseJsonFile(std::string path, json11::Json& j);
}
