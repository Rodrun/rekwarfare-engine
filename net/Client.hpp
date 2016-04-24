#pragma once

#include "NetTypes.hpp"

#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define DEFAULT_PLAYERNAME "Player"

namespace rekwarfare {

/*
* The client's job is to represent an actual client; meaning
*  it will store the client's socket descriptor and use it
*  to send data to the socket and use the descriptor for any
*  of your needs.
* Its functions do the same as Socket's, if you want
*  documentation, for some reason, look at Socket.hpp.
*/
class Client {
public:
    Client(socketdsc, protocol p=PROTOCOL_TCP);
    ~Client();
    int message(std::string data, int flags=0);
    socketdsc socket;
    std::string name = DEFAULT_PLAYERNAME;

private:
    protocol m_protocol;
};

}
