#include "Protocol.hpp"

#include "util/Ustring.h"

#include <string>
#include <vector>

namespace rekwarfare {

#define constring const std::string

std::string getResponseValue(std::string m) {
    auto parsed = parse(m, respond_PREFIX);
    // reponse composed of RES:<TYPE>:<DATA>
    if (parsed.size() <= 2)
        return "";

    std::string cut;
    for (size_t i = 2; i < parsed.size(); i++) {
        cut += parsed[i];
    }
    return cut;
}

std::string buildResponse(std::string r, std::string d) {
    return r + d;
}

std::string buildGreetResponse(std::string pn) {
    return buildResponse(respond_greet, pn);
}

// BOTH

constring respond_DELIMETER = ":";
constring respond_PREFIX = "RES" + respond_DELIMETER;
constring request_DELIMETER = ":";
constring request_PREFIX = "ASK" + respond_DELIMETER;

// will change greetings later...
constring respond_greet = respond_PREFIX + "GREET" + respond_DELIMETER;
constring respond_name = respond_PREFIX + "NAME" + respond_DELIMETER;

constring request_greet = request_PREFIX + "GREET" + request_DELIMETER;
constring request_name = request_PREFIX + "NAME" + request_DELIMETER;

// TO SERVER
constring request_map = request_PREFIX + "MAP";

// TO CLIENT

}
