#include "Configuration.hpp"

#include "util/UFile.h"
#include "util/Ujson.h"
#include "util/Ustring.h"

#include "lib/json11/json11.hpp"

#include "SDL2/SDL.h"

#include <fstream>
#include <string>

namespace rekwarfare {

bool readConfig(std::string cnfpath, Configuration& cnf,
    HUDConfiguration& hcnf) {
    json11::Json jsonconfig;
    std::string err = parseJsonFile(cnfpath, jsonconfig);
    if (!err.empty()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Reading config file: %s", err.c_str());
        return false;
    }

    // Assignment
    if (toUpperCase(jsonconfig["show_intro"].string_value()).compare("true")
        == 0) cnf.show_intro = true;
    if (toUpperCase(jsonconfig["show_fps"].string_value()).compare("true")
        == 0) cnf.show_fps = true;
    if (toUpperCase(jsonconfig["dev_console"].string_value()).compare("true")
        == 0) cnf.dev_console = true;
    cnf.audio_chunksize = jsonconfig["audio_chunksize"].int_value();
    cnf.language = new Language(jsonconfig["language-directory"].string_value()
        + jsonconfig["language"].string_value() + ".json");

    // TODO: Read HUD config
    SDL_Log("HUD Config reading not supported yet!");

    return true;
}

}
