#include "Client.hpp"

#include "NetTypes.hpp"

#include <cstring> // strerror
#include <string>
#include <cerrno>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace rekwarfare {

Client::Client(socketdsc s, protocol p) :
    socket(s), m_protocol(p) { }

Client::~Client() {
    int result = close(socket);
    if (result == -1) {
        std::cout << "Closing client socket: " << strerror(errno) << std::endl;
    }
}

int Client::message(std::string data, int flags) {
    if (m_protocol == PROTOCOL_TCP) {
        int result = 0;
        result = send(socket, data.c_str(), data.length(), flags);
        // Not sure if EAGAIN/EWOULDBLOCK would be necessary to check~
        if (result == -1 && (errno != EAGAIN || errno != EWOULDBLOCK)) {
            std::cout << "send(): " << strerror(errno) << std::endl;
            return -1;
        }
    } // TODO: implement UDP support
    return 0;
}

}
