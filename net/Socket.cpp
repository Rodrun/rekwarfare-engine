#include "Socket.hpp"

#include "NetTypes.hpp"

#include <cstring> // memset
#include <string>
#include <cerrno>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>

namespace rekwarfare {

Socket::Socket(int mrl) : m_max_recieve_length(mrl) { }

Socket::~Socket() {
    std::cout << "Closing socket." << std::endl;
    disconnect();
}

int Socket::join(std::string host, std::string port, const protocol p) {
    m_protocol = p;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints)); // empty struct
    hints.ai_family = AF_UNSPEC; // both ipv4/6 support
    if (p == PROTOCOL_TCP)
        hints.ai_socktype = PROTOCOL_TCP;
    else
        hints.ai_socktype = PROTOCOL_UDP;

    int gaistatus = getaddrinfo(host.c_str(), port.c_str(), &hints,
        &m_serverinfo);
    if (gaistatus != 0) {
        std::cout << "getaddrinfo(): " << gai_strerror(gaistatus) << std::endl;
        return -1;
    }

    m_socket = socket(m_serverinfo->ai_family, m_serverinfo->ai_socktype,
        m_serverinfo->ai_protocol);
    if (m_socket == -1) {
        std::cout << "socket(): " << strerror(errno) << std::endl;
        return m_socket;
    }

    int cnstatus = connect(m_socket, m_serverinfo->ai_addr,
        m_serverinfo->ai_addrlen);
    if (cnstatus != 0) {
        std::cout << "connect(): " << strerror(errno) << std::endl;
        return cnstatus;
    }

    fcntl(m_socket, F_SETFL, O_NONBLOCK);

    freeaddrinfo(m_serverinfo);
    return 0;
}

int Socket::message(std::string data, int flags) {
    int result;
    if (m_protocol == PROTOCOL_TCP) {
        result = send(m_socket, data.c_str(), data.length(), flags);
        // Not sure if EAGAIN/EWOULDBLOCK would be necessary to check~
        if (result == -1 && (errno != EAGAIN || errno != EWOULDBLOCK))
            std::cout << "send(): " << strerror(errno) << std::endl;
    } // TODO: implement UDP support
    return result;
}

std::string Socket::recieve(int flags) {
    std::string result;
    int recvresult = recv(m_socket, &result, sizeof result,
        flags);
    if (recvresult == -1 && (errno != EAGAIN || errno != EWOULDBLOCK)) {
        std::cout << "recv(): " << strerror(errno) << std::endl;
    } else if (recvresult == 0) {
        delete this;
    }
    return result;
}

void Socket::disconnect() {
    close(m_socket);
}

}
