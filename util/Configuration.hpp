#pragma once

#include "Language.hpp"

#include "lib/json11/json11.hpp"

#include <string>

namespace rekwarfare {

struct HUDConfiguration {
};

struct Configuration {
    Language* language = nullptr;
//    HUD* hud = nullptr;
    bool show_intro = true;
    bool show_fps = false;
    bool dev_console = false;
    int audio_chunksize = 2024;
};

/*
* Read the configuration files and give each struct proper values.
* langdir: The directory where the language files are.
* cnfpath: Path to the configuration file.
* returns: true on success, false otherwise
*/
bool readConfig(std::string cnfpath, Configuration&, HUDConfiguration&);

}
