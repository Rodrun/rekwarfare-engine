#pragma once

/*
* Defined strings that comply to the client-server
*  protocol. Just simply use one of these strings
*  to the other end of the connection to ask for
*  something or to respond to a request. If you
*  are responding to a request, use buildResponse().
*/

#include <string>

#define externc extern const

namespace rekwarfare {

/*
* Extracts the message from a given -- full --
*  message.
* returns: response data
*/
std::string getResponseValue(std::string);
/*
* Build a response string compliant to the protocol,
*  equivalent of respons + data
*/
std::string buildResponse(std::string response, std::string data);
/*
* Build a greeting response, equivalent to:
*  buildResponse(respond_greet, "<name of player or server>");
*/
std::string buildGreetResponse(std::string playername);

externc std::string respond_PREFIX;
externc std::string respond_DELIMETER;
externc std::string request_PREFIX;
externc std::string request_DELIMETER;

externc std::string respond_greet;
externc std::string respond_name;

externc std::string request_greet;
externc std::string request_name;

// TO SERVER (_ts_)
typedef char PlayerMoveAction;
constexpr PlayerMoveAction MVT_NULL             = -1;
constexpr PlayerMoveAction MVT_JUMP             =  0;
constexpr PlayerMoveAction MVT_LEFT             =  1;
constexpr PlayerMoveAction MVT_RIGHT            =  2;

typedef char PlayerWeaponAction;
constexpr PlayerWeaponAction WEP_NULL               = -1;
/*
* In case weapons can be given multiple "firing types" or some sort:
*  'F1' is the "default" firing method.
*/
constexpr PlayerWeaponAction WEP_SHOOT_F1           =  0;
constexpr PlayerWeaponAction WEP_RELOAD             =  1;
constexpr PlayerWeaponAction WEP_SWITCH_NEXT        =  2;
constexpr PlayerWeaponAction WEP_SWITCH_PREV        =  3;

typedef struct {
    PlayerMoveAction moveaction = MVT_NULL;
    PlayerWeaponAction weaponaction = WEP_NULL;
} PlayerNetworkAction;

externc std::string request_ts_map;

// TO CLIENT (_tc_)

}
