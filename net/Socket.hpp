#pragma once

#include "NetTypes.hpp"

#include <string>

#include <sys/types.h>
#ifdef _WIN32
#else
#	include <sys/socket.h>
#	include <netdb.h>
#endif

namespace rekwarfare {

constexpr int DEFAULT_MAX_RECVLENGTH = 1025;

class Socket {
public:
    Socket(int maxrecvlen=DEFAULT_MAX_RECVLENGTH);
    ~Socket();
    /*
    * Connect to a server with given hostname and port
    * returns: 0 on success, error code on fail
    */
    int join(std::string host, std::string port,
        const protocol p=PROTOCOL_TCP);
    /*
    * Send a message to the server
    * returns: bytes sent on success, -1 on fail
    */
    int message(std::string data, int flags=0);
    /*
    * Get recieved data
    * returns: bytes recieved on success, -1 on fail
    */
    std::string recieve(int flags=0);
    void disconnect();

private:
    std::string m_host, m_port;
    struct addrinfo* m_serverinfo;
    socketdsc m_socket;
    protocol m_protocol;
    int m_max_recieve_length = 0;
};

}
